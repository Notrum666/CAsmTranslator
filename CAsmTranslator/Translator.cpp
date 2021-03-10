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

	identifiers->add(new Record_Identifiers((char*)"test", (void*)5, (Type*)Type::type_int));
	identifiers->add(new Record_Identifiers((char*)"test2", (void*)6, (Type*)Type::type_int));
	//
	//Record_Identifiers* r = new Record_Identifiers((char*)"test", (void*)10, (Type*)Type::type_int);
	//int id = identifiers->getIdByName((char*)r->name);
	//if (id != -1)
	//	printf_s("Record with this name is already exists\n");
	//identifiers->print();
	//printf_s("id of \"test500\" : %d\n", identifiers->getIdByName((char*)"test500"));
	//int* value = (int*)std::malloc(sizeof(int));
	//*value = 5;
	//constants->add(new Record_Constants((void*)((int*)value), Type::type_int));
	//value = (int*)std::malloc(sizeof(int));
	//*value = 6;
	//constants->add(new Record_Constants((void*)((int*)value), Type::type_int));
	//constants->add(new Record_Constants());

	//Record_Identifiers* r = new Record_Identifiers((char*)"test", (void*)10, (Type*)Type::type_int);
	//value = (int*)std::malloc(sizeof(int));
	//*value = 500;
	//int id = constants->getIdByValue((void*)value);
	//if (id != -1)
	//	printf_s("Record with this name is already exists\n");
	//constants->print();
	//printf_s("id of \"500\" : %d\n", constants->getIdByValue((void*)value));

	//keywords->print();
	//char* wordToSearch = (char*)"help";
	//int id = keywords->getIdByKeyword(wordToSearch);
	//printf_s("id of %s : %d", wordToSearch, id);

	//terminalSymbols->print();
	//char symbolToSearch = '[';
	//int id = terminalSymbols->getIdBySymbol(symbolToSearch);
	//printf_s("id of \"[\" : %d", id);
	Record_Identifiers* record = identifiers->get(1);
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

	int statesCount = 4;

	const char** stateTable = (char**)std::malloc(statesCount * sizeof(char*));
	stateTable[0] = "\0\1\2\3";
	stateTable[1] = "\0\0\0\0";
	stateTable[2] = "\0\0\0\0";
	stateTable[3] = "\0\0\0\0";

	State state = State::Start;
	while (!feof(file_in))
	{
		switch (state)
		{
		case State::Start:

			break;
		case State::Digit:
			break;
		case State::Letter:
			break;
		case State::Slash:
			break;
		}
	}

	//while ((cur = std::fgetc(file_in)) != EOF)
	//{
	//	short symbolId = terminalSymbols->getIdBySymbol(cur);
	//	if (symbolId == -1)
	//		buffer[pos++] = cur;
	//	else
	//	{
	//		if (pos > 0)
	//		{
	//			Token* token = generateToken(buffer);
	//			if (token == nullptr)
	//				return false;
	//			tokens.push_back(token);
	//			printf_s("(%d|%d) ", token->table_id, token->record_id);
	//			while (pos > 0)
	//				buffer[--pos] = 0;
	//		}
	//		if (!terminalSymbols->get(symbolId)->skip)
	//		{
	//			Token* token = new Token(1, symbolId);
	//			tokens.push_back(token);
	//			printf_s("(%d|%d) ", token->table_id, token->record_id);
	//		}
	//		else
	//			if (cur == '\n')
	//				printf_s("\n");
	//	}
	//}

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