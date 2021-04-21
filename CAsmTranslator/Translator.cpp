#include "Translator.h"
#include "Error.h"

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
	keywords->add(new Record_Keywords("+"));
	keywords->add(new Record_Keywords("-"));
	keywords->add(new Record_Keywords("!"));
	keywords->add(new Record_Keywords("<"));
	keywords->add(new Record_Keywords(">"));
	keywords->add(new Record_Keywords("=="));
	keywords->add(new Record_Keywords("+="));
	keywords->add(new Record_Keywords("-="));
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

Error* Translator::TranslateFile(const char* pathFrom, const char* pathTo)
{
	FILE* file_in, *file_out;
	if (fopen_s(&file_in, pathFrom, "r"))
		return new Error(pathFrom, 0, 0, "Cant open file");
	if(fopen_s(&file_out, pathTo, "w"))
		return new Error(pathTo, 0, 0, "Cant open file");

	std::vector<Token*> tokens = std::vector<Token*>();

	char* buffer = (char*)std::calloc(MAX_IDENTIFIER_LENGTH, sizeof(char));
	int pos = 0;
	int cur = 0;
	char* curChar = (char*)std::calloc(2, sizeof(char));

	StateGraph graph = StateGraph();
	Error* err;
	bool foundPath;
	int curColumn = 1, curRow = 1;
	while ((cur = fgetc(file_in)) != -1)
	{
		curColumn++;
		if (cur == '\n')
		{
			curRow++;
			curColumn = 0;
		}

		*curChar = cur;
		foundPath = false;
		for (auto path : graph.curNode->paths)
		{
			if (std::regex_match(curChar, *path->regex))
			{
				foundPath = true;
				if (path->destination != graph.curNode)
				{
					if (err = graph.curNode->getResult(buffer, &tokens))
					{
						err->file = pathFrom;
						err->row = curRow;
						err->column = curColumn;
						return err;
					}
					while (pos > 0)
						buffer[--pos] = 0;
					graph.curNode = path->destination;
				}
				buffer[pos++] = cur;
				break;
			}
		}
		if (!foundPath)
			return new Error(pathFrom, curRow, curColumn, "undefined symbol");
	}

	if (err = graph.curNode->getResult(buffer, &tokens))
	{
		err->file = pathFrom;
		err->row = curRow;
		err->column = curColumn;
		return err;
	}
	while (pos > 0)
		buffer[--pos] = 0;

	for (auto token : tokens)
	{
		if (token->table_id == 1)
		{
			if (token->record_id == 1)
				fprintf_s(file_out, "\n");
			else if (token->record_id == 2)
				fprintf_s(file_out, "\t");
			else
				fprintf_s(file_out, "(%d,%d)", token->table_id, token->record_id);
		}
		else
			fprintf_s(file_out, "(%d,%d)", token->table_id, token->record_id);
	}
	fclose(file_in);
	fclose(file_out);
	return nullptr;
}