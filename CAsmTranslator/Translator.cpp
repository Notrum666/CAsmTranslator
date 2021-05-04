#include "Translator.h"
#include "Error.h"

Table_Keywords* Translator::keywords = new Table_Keywords();
Table_Delimeters* Translator::delimeters = new Table_Delimeters();
Table_Identifiers* Translator::identifiers = new Table_Identifiers();
Table_Constants* Translator::constants = new Table_Constants();
ParsingTable* Translator::parsingTable = new ParsingTable();

void Translator::Init()
{	
	keywords->add(new Record_Keywords("int"));
	keywords->add(new Record_Keywords("while"));
	keywords->add(new Record_Keywords("do"));
	keywords->add(new Record_Keywords("="));
	keywords->add(new Record_Keywords("+"));
	keywords->add(new Record_Keywords("-"));
	keywords->add(new Record_Keywords("<"));
	keywords->add(new Record_Keywords(">"));
	keywords->add(new Record_Keywords("=="));
	keywords->add(new Record_Keywords("+="));
	keywords->add(new Record_Keywords("-="));
	keywords->add(new Record_Keywords("<="));
	keywords->add(new Record_Keywords(">="));
	keywords->add(new Record_Keywords("!="));

	delimeters->add(new Record_Delimeters(' ', true)); // 0
	delimeters->add(new Record_Delimeters('\n', true)); // 1
	delimeters->add(new Record_Delimeters('\t', true)); // 2
	delimeters->add(new Record_Delimeters(';', false)); // 3
	delimeters->add(new Record_Delimeters('{', false)); // 4
	delimeters->add(new Record_Delimeters('}', false)); // 5
	delimeters->add(new Record_Delimeters('(', false)); // 6
	delimeters->add(new Record_Delimeters(')', false)); // 7
	delimeters->add(new Record_Delimeters(',', false)); // 8

	//parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 0) }, 0, false, false, false, false));

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 0) }, 1, false, false, false, true)); // 1: Func

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 0) }, 2, true, false, false, true)); // 2: type
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(2, -1) }, 3, true, false, false, true)); // 3: identifier
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 6) }, 4, true, false, false, true)); // 4: (
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 7) }, 5, true, false, false, true)); // 5: )
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 4) }, 6, true, false, false, true)); // 6: {
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3), Token(0, 0), Token(2, -1), Token(3, -1), 
														   Token(1, 6), Token(0, 1), Token(0, 2), Token(1, 5) }, 8, true, true, false, true)); // 7: Body
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 5) }, 0, true, false, true, true)); // 8: }

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3), Token(0, 0), Token(2, -1), Token(3, -1),
														   Token(1, 6), Token(0, 1), Token(0, 2), Token(1, 5) }, 10, false, false, false, false)); // 9: Body1
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 5) }, 12, false, false, false, true)); // 10: Body2

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3), Token(0, 0), Token(2, -1), Token(3, -1),
														   Token(1, 6), Token(0, 1), Token(0, 2) }, 13, false, true, false, true)); // 11: Action
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3), Token(0, 0), Token(2, -1), Token(3, -1),
														   Token(1, 6), Token(0, 1), Token(0, 2), Token(1, 5) }, 8, false, false, false, true)); // 12: Body

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 5) }, 0, false, false, true, true));  // 13: Empty

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3) }, 18, false, false, false, false)); // 14: Action1
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 0) }, 19, false, false, false, false)); // 15: Action2
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(2, -1), Token(3, -1), Token(1, 6) }, 21, false, false, false, false)); // 16: Action3
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 1) }, 23, false, false, false, false)); // 17: Action4
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 2) }, 24, false, false, false, true)); // 18: Action5

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3) }, 0, true, false, true, true)); // 19: ;

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 0) }, 26, false, true, false, true)); // 20: Declaration
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3) }, 0, true, false, true, true)); // 21: ;

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(2, -1), Token(3, -1), Token(1, 6) }, 27, false, true, false, true)); // 22: Expression
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3) }, 0, true, false, true, true)); // 23: ;

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 1) }, 30, false, false, false, true)); // 24: While

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 2) }, 31, false, true, false, true)); // 25: DoWhile
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3) }, 0, true, false, true, true)); // 26: ;


	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 0) }, 32, false, false, false, true)); // 27: Declaration1

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(2, -1) }, 36, false, false, false, false)); // 28: Expression1
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(3, -1) }, 38, false, false, false, false)); // 29: Expression2
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 6) }, 40, false, false, false, true)); // 30: Expression3

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 1) }, 44, false, false, false, true)); // 31: While1

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 2) }, 49, false, false, false, true)); // 32: DoWhile1

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 0) }, 33, true, false, false, true)); // 33: type
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(2, -1) }, 34, true, false, false, true)); // 34: identifier
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(2, -1), Token(3, -1), Token(1, 6), Token(1, 8), Token(1, 3) }, 57, false, true, false, true)); // 35: Value
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 8), Token(1, 3) }, 59, false, false, false, true)); // 36: Tail

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(2, -1) }, 37, true, false, false, true)); // 37: identifier
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 3), Token(0, 4), Token(0, 5), 
														   Token(0, 6), Token(0, 7), Token(0, 8), 
														   Token(0, 9), Token(0, 10), Token(0, 11), 
														   Token(0, 12), Token(0, 13), Token(1, 3),
														   Token(1, 7) }, 61, false, false, false, true)); // 38: Expression_Tail

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(3, -1) }, 39, true, false, false, true)); // 39: constant
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 4), Token(0, 5), Token(0, 6),
														   Token(0, 7), Token(0, 8), Token(0, 9),
														   Token(0, 12), Token(0, 13), Token(1, 3),
														   Token(1, 7) }, 63, false, false, false, true)); // 40: NAExpression_Tail

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 6) }, 41, true, false, false, true)); // 41: (
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(2, -1), Token(3, -1), Token(1, 6) }, 27, false, true, false, true)); // 42: Expression
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 7) }, 43, true, false, false, true)); // 43: )
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 3), Token(0, 4), Token(0, 5),
														   Token(0, 6), Token(0, 7), Token(0, 8),
														   Token(0, 9), Token(0, 10), Token(0, 11),
														   Token(0, 12), Token(0, 13), Token(1, 3),
														   Token(1, 7), Token(1, 8) }, 61, false, false, false, true)); // 44: Expression_Tail

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 1) }, 45, true, false, false, true)); // 45: while
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 6) }, 46, true, false, false, true)); // 46: (
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(2, -1), Token(3, -1), Token(1, 6) }, 27, false, true, false, true)); // 47: Expression
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 7) }, 48, true, false, false, true)); // 48: )
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 4), Token(1, 3), Token(0, 0), Token(2, -1),
														   Token(3, -1), Token(1, 6), Token(0, 1), Token(0, 2) }, 65, false, false, false, true)); // 49: WhileBody

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 2) }, 50, true, false, false, true)); // 50: do
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 4) }, 51, true, false, false, true)); // 51: {
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3), Token(0, 0), Token(2, -1), Token(3, -1),
														   Token(1, 6), Token(0, 1), Token(0, 2), Token(0, 3), Token(1, 5) }, 8, false, false, false, true)); // 52: Body
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 5) }, 53, true, false, false, true)); // 53: }
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 2) }, 54, true, false, false, true)); // 54: while
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 6) }, 55, true, false, false, true)); // 55: (
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(2, -1), Token(3, -1), Token(1, 6) }, 56, false, true, false, true)); // 56: Expression
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 7) }, 0, true, false, true, true)); // 57: )


	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 3) }, 67, false, false, false, false)); // 58: Value1
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 8), Token(1, 3) }, 69, false, false, false, true)); // 59: Value2

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 8) }, 70, false, false, false, false)); // 60: Tail1
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3) }, 74, false, false, false, true)); // 61: Tail2

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 3), Token(0, 4), Token(0, 5), Token(0, 6), 
														   Token(0, 7), Token(0, 8), Token(0, 9), Token(0, 10), 
														   Token(0, 11), Token(0, 12), Token(0, 13) }, 75, false, false, false, false)); // 62: Expression_Tail1
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 7), Token(1, 3), Token(1, 8) }, 77, false, false, false, true)); // 63: Expression_Tail2

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 4), Token(0, 5), Token(0, 6), Token(0, 7), 
														   Token(0, 8), Token(0, 11), Token(0, 12), Token(0, 13) }, 78, false, false, false, false)); // 64: NAExpression_Tail1
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 7), Token(1, 3), Token(1, 8) }, 80, false, false, false, true)); // 65: NAExpression_Tail2

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 0), Token(1, 3), Token(2, -1), Token(3, -1), Token(0, 1), Token(0, 2) }, 84, false, false, false, false)); // 66: WhileBody1
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3) }, 81, false, false, false, true)); // 67: WhileBody2

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 3) }, 68, true, false, false, true)); // 68: =
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(2, -1), Token(3, -1), Token(1, 6)  }, 27, false, false, false, true)); // 69: Expression

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 8), Token(1, 3) }, 0, false, false, true, true)); // 70: Empty

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3) }, 71, true, false, false, true)); // 71: ,
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(2, -1) }, 72, true, false, false, true)); // 72: identifier
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3), Token(1, 8), Token(0, 3) }, 57, false, true, false, true)); // 73: Value
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3), Token(1, 8) }, 59, false, false, false, true)); // 74: Tail

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3), Token(1, 8) }, 0, false, false, true, true)); // 75: Empty

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 3), Token(0, 4), Token(0, 5),
														   Token(0, 6), Token(0, 7), Token(0, 8),
														   Token(0, 9), Token(0, 10), Token(0, 11),
														   Token(0, 12), Token(0, 13) }, 85, false, true, false, true)); // 76: Operation
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(2, -1), Token(3, -1), Token(1, 6) }, 27, false, false, false, true)); // 77: Expression

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3), Token(1, 7), Token(1, 8) }, 0, false, false, true, true)); // 78: Empty

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 3), Token(0, 4), Token(0, 5),
														   Token(0, 6), Token(0, 7) }, 96, false, true, false, true)); // 79: NAOperation
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(2, -1), Token(3, -1), Token(1, 6) }, 27, false, false, false, true)); // 80: Expression

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 7), Token(1, 3), Token(1, 8) }, 0, false, false, true, true)); // 81: Empty

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 4) }, 82, true, false, false, true)); // 82: {
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3), Token(0, 0), Token(2, -1), Token(3, -1),
														   Token(1, 6), Token(0, 1), Token(0, 2), Token(1, 5) }, 8, false, true, false, true)); // 83: Body
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 5) }, 0, true, false, true, true)); // 84: }

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(1, 3), Token(0, 0), Token(2, -1), Token(3, -1), Token(0, 1), Token(0, 2) }, 13, false, false, false, true)); // 85: Action


	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 3) }, 104, false, false, false, false)); // 86: Operation1
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 4) }, 105, false, false, false, false)); // 87: Operation2
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 5) }, 106, false, false, false, false)); // 88: Operation3
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 6) }, 107, false, false, false, false)); // 89: Operation4
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 7) }, 108, false, false, false, false)); // 90: Operation5
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 8) }, 119, false, false, false, false)); // 91: Operation6
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 9) }, 110, false, false, false, false)); // 92: Operation7
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 10) }, 111, false, false, false, false)); // 93: Operation8
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 11) }, 112, false, false, false, false)); // 94: Operation9
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 12) }, 113, false, false, false, false)); // 95: Operation10
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 13) }, 114, false, false, false, true)); // 96: Operation11

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 4) }, 115, false, false, false, false)); // 97: NAOperation1
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 5) }, 116, false, false, false, false)); // 98: NAOperation2
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 6) }, 117, false, false, false, false)); // 99: NAOperation3
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 7) }, 118, false, false, false, false)); // 100: NAOperation4
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 8) }, 119, false, false, false, false)); // 101: NAOperation5
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 11) }, 120, false, false, false, false)); // 102: NAOperation6
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 12) }, 121, false, false, false, false)); // 103: NAOperation7
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 13) }, 122, false, false, false, true)); // 104: NAOperation8

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 3) }, 0, false, false, true, true)); // 105: =
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 4) }, 0, false, false, true, true)); // 106: +
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 5) }, 0, false, false, true, true)); // 107: -
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 6) }, 0, false, false, true, true)); // 108: <
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 7) }, 0, false, false, true, true)); // 109: >
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 8) }, 0, false, false, true, true)); // 110: ==
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 9) }, 0, false, false, true, true)); // 111: +=
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 10) }, 0, false, false, true, true)); // 112: -=
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 11) }, 0, false, false, true, true)); // 113: <
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 12) }, 0, false, false, true, true)); // 114: >
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 13) }, 0, false, false, true, true)); // 115: !=

	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 4) }, 0, false, false, true, true)); // 116: +
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 5) }, 0, false, false, true, true)); // 117: -
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 6) }, 0, false, false, true, true)); // 118: <
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 7) }, 0, false, false, true, true)); // 119: >
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 8) }, 0, false, false, true, true)); // 120: ==
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 11) }, 0, false, false, true, true)); // 121: <
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 12) }, 0, false, false, true, true)); // 122: >
	parsingTable->add(new ParsingTable_Record(new Token[]{ Token(0, 13) }, 0, false, false, true, true)); // 123: !=
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