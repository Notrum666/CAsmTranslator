#include "Translator.h"

Table_Keywords* Translator::keywords = new Table_Keywords();
Table_Delimeters* Translator::delimeters = new Table_Delimeters();
Table_Identifiers* Translator::identifiers = new Table_Identifiers();
Table_Constants* Translator::constants = new Table_Constants();

void Translator::Init()
{	
	keywords->add(new Record_Keywords("int"));
	keywords->add(new Record_Keywords("while"));
	keywords->add(new Record_Keywords("do"));
	keywords->add(new Record_Keywords("="));
	keywords->add(new Record_Keywords("<"));
	keywords->add(new Record_Keywords(">"));
	keywords->add(new Record_Keywords("=="));
	keywords->add(new Record_Keywords("<="));
	keywords->add(new Record_Keywords(">="));
	keywords->add(new Record_Keywords("!="));

	delimeters->add(new Record_Delimeters(' ', true));
	delimeters->add(new Record_Delimeters('\n', false));
	delimeters->add(new Record_Delimeters('\t', false));
	delimeters->add(new Record_Delimeters(';', false));
	delimeters->add(new Record_Delimeters('{', false));
	delimeters->add(new Record_Delimeters('}', false));
	delimeters->add(new Record_Delimeters('(', false));
	delimeters->add(new Record_Delimeters(')', false));
}

bool Translator::TranslateFile(const char* pathFrom, const char* pathTo)
{
	FILE* file_in;
	if (fopen_s(&file_in, pathFrom, "r"))
		return false;

	std::vector<Token*> tokens = std::vector<Token*>();

	char* buffer = (char*)std::calloc(MAX_IDENTIFIER_LENGTH, sizeof(char));
	int pos = 0;
	int cur = 0;
	char* curChar = (char*)std::calloc(2, sizeof(char));

	StateGraph graph = StateGraph();
	bool foundPath;
	while ((cur = fgetc(file_in)) != -1)
	{
		*curChar = cur;
		foundPath = false;
		for (auto path : graph.curNode->paths)
		{
			if (std::regex_match(curChar, *path->regex))
			{
				foundPath = true;
				if (path->destination != graph.curNode)
				{
					if (!graph.curNode->getResult(buffer, &tokens))
						return false;
					while (pos > 0)
						buffer[--pos] = 0;
					graph.curNode = path->destination;
				}
				buffer[pos++] = cur;
				break;
			}
		}
		if (!foundPath)
			return false;
	}
	if (!graph.curNode->getResult(buffer, &tokens))
		return false;
	while (pos > 0)
		buffer[--pos] = 0;

	for (auto token : tokens)
	{
		if (token->table_id == 1)
		{
			if (token->record_id == 1)
				printf_s("\n");
			else if (token->record_id == 2)
				printf_s("\t");
			else
				printf_s("(%d,%d)", token->table_id, token->record_id);
		}
		else
			printf_s("(%d,%d)", token->table_id, token->record_id);
	}

	return true;
}

//Token* Translator::generateToken(char* text)
//{
//	int id;
//	id = keywords->getIdByKeyword(text);
//	if (id != -1)
//		return new Token(0, id);
//	if (text[0] == '-' || text[0] >= '0' && text[0] <= '9')
//	{
//		char* ptr = text;
//		while (*(++ptr) != '\0')
//			if (*ptr < '0' || *ptr > '9')
//				return nullptr;
//		int* value = (int*)std::malloc(sizeof(int));
//		*value = std::atoi(text);
//		id = constants->getIdByValue((void*)value);
//		if (id == -1)
//			return new Token(3, constants->add(new Record_Constants((void*)value, Type::type_int)));
//		else
//			return new Token(3, id);
//	}
//	if (text[0] >= 'a' && text[0] <= 'z' || text[0] >= 'A' && text[0] <= 'Z' || text[0] == '_')
//	{
//		char* ptr = text;
//		while (*(++ptr) != '\0')
//			if (!(text[0] >= 'a' && text[0] <= 'z' ||
//				text[0] >= 'A' && text[0] <= 'Z' ||
//				text[0] >= '0' && text[0] <= '9' ||
//				text[0] == '_'))
//				return nullptr;
//		size_t size = std::strlen(text) + 1;
//		char* name = new char[size];
//		strcpy_s(name, size, text);
//		id = identifiers->getIdByName(name);
//		if (id == -1)
//			return new Token(2, identifiers->add(new Record_Identifiers(name, nullptr, nullptr)));
//		else
//			return new Token(2, id);
//	}
//	return nullptr;
//}