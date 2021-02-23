#include "Translator.h"

Translator::Translator()
{
	keywords = new Table_Keywords();
	terminalSymbols = new Table_TerminalSymbols();
	identifiers = new Table_Identifiers();
	constants = new Table_Constants();
	
	keywords->add(new Record_Keywords("int"));
	keywords->add(new Record_Keywords("while"));
	keywords->add(new Record_Keywords("do"));
	keywords->add(new Record_Keywords("<"));
	keywords->add(new Record_Keywords(">"));
	keywords->add(new Record_Keywords("=="));
	keywords->add(new Record_Keywords("<="));
	keywords->add(new Record_Keywords(">="));
	keywords->add(new Record_Keywords("!="));

	terminalSymbols->add(new Record_TerminalSymbols(' ', true));
	terminalSymbols->add(new Record_TerminalSymbols('\n', true));
	terminalSymbols->add(new Record_TerminalSymbols('\t', true));
	terminalSymbols->add(new Record_TerminalSymbols(';', false));
	terminalSymbols->add(new Record_TerminalSymbols('{', false));
	terminalSymbols->add(new Record_TerminalSymbols('}', false));
	terminalSymbols->add(new Record_TerminalSymbols('(', false));
	terminalSymbols->add(new Record_TerminalSymbols(')', false));
	terminalSymbols->add(new Record_TerminalSymbols('=', false));
}

bool Translator::translateFile(const char* pathFrom, const char* pathTo)
{
	FILE* file_in;
	if (fopen_s(&file_in, pathFrom, "r"))
		return false;

	std::vector<Token*> tokens = std::vector<Token*>();

	char* buffer = (char*)std::calloc(MAX_IDENTIFIER_LENGTH, sizeof(char));
	int pos = 0;
	int cur = 0;

	while ((cur = std::fgetc(file_in)) != EOF)
	{
		short symbolId = terminalSymbols->getIdBySymbol(cur);
		if (symbolId == -1)
			buffer[pos++] = cur;
		else
		{
			if (pos > 0)
			{
				Token* token = generateToken(buffer);
				if (token == nullptr)
					return false;
				tokens.push_back(token);
				printf_s("(%d|%d) ", token->table_id, token->record_id);
				while (pos > 0)
					buffer[--pos] = 0;
			}
			if (!terminalSymbols->get(symbolId)->skip)
			{
				Token* token = new Token(1, symbolId);
				tokens.push_back(token);
				printf_s("(%d|%d) ", token->table_id, token->record_id);
			}
			else
				if (cur == '\n')
					printf_s("\n");
		}
	}

	return true;
}

Token* Translator::generateToken(char* text)
{
	int id;
	id = keywords->getIdByKeyword(text);
	if (id != -1)
		return new Token(0, id);
	if (text[0] == '-' || text[0] >= '0' && text[0] <= '9')
	{
		char* ptr = text;
		while (*(++ptr) != '\0')
			if (*ptr < '0' || *ptr > '9')
				return nullptr;
		int* value = (int*)std::malloc(sizeof(int));
		*value = std::atoi(text);
		id = constants->getIdByValue((void*)value);
		if (id == -1)
			return new Token(3, constants->add(new Record_Constants((void*)value, Type::type_int)));
		else
			return new Token(3, id);
	}
	if (text[0] >= 'a' && text[0] <= 'z' || text[0] >= 'A' && text[0] <= 'Z' || text[0] == '_')
	{
		char* ptr = text;
		while (*(++ptr) != '\0')
			if (!(text[0] >= 'a' && text[0] <= 'z' ||
				text[0] >= 'A' && text[0] <= 'Z' ||
				text[0] >= '0' && text[0] <= '9' ||
				text[0] == '_'))
				return nullptr;
		size_t size = std::strlen(text) + 1;
		char* name = new char[size];
		strcpy_s(name, size, text);
		id = identifiers->getIdByName(name);
		if (id == -1)
			return new Token(2, identifiers->add(new Record_Identifiers(name, nullptr, nullptr)));
		else
			return new Token(2, id);
	}
	return nullptr;
}