#include "Translator.h"
#include "Error.h"

#define TABLE_KEYWORDS 0
#define TABLE_DELIMETERS 1
#define TABLE_IDENTIFIERS 2
#define TABLE_CONSTANTS 3

#define MESSAGE_LEN 100

Table_Keywords* Translator::keywords = new Table_Keywords();
Table_Delimeters* Translator::delimeters = new Table_Delimeters();
Table_Identifiers* Translator::identifiers = new Table_Identifiers();
Table_Constants* Translator::constants = new Table_Constants();
ParsingTable* Translator::parsingTable = new ParsingTable();

void Translator::Init()
{	
	keywords->add(new Record_Keywords("int")); // 0
	keywords->add(new Record_Keywords("while")); // 1
	keywords->add(new Record_Keywords("do")); // 2
	keywords->add(new Record_Keywords("=")); // 3
	keywords->add(new Record_Keywords("+")); // 4
	keywords->add(new Record_Keywords("-")); // 5
	keywords->add(new Record_Keywords("<")); // 6
	keywords->add(new Record_Keywords(">")); // 7
	keywords->add(new Record_Keywords("==")); // 8
	keywords->add(new Record_Keywords("+=")); // 9
	keywords->add(new Record_Keywords("-=")); // 10
	keywords->add(new Record_Keywords("<=")); // 11
	keywords->add(new Record_Keywords(">=")); // 12
	keywords->add(new Record_Keywords("!=")); // 13

	delimeters->add(new Record_Delimeters(' ', true)); // 0
	delimeters->add(new Record_Delimeters('\n', true)); // 1
	delimeters->add(new Record_Delimeters('\t', true)); // 2
	delimeters->add(new Record_Delimeters(';', false)); // 3
	delimeters->add(new Record_Delimeters('{', false)); // 4
	delimeters->add(new Record_Delimeters('}', false)); // 5
	delimeters->add(new Record_Delimeters('(', false)); // 6
	delimeters->add(new Record_Delimeters(')', false)); // 7
	delimeters->add(new Record_Delimeters(',', false)); // 8
	
	//parsingTable->add(new ParsingTable_Record(new Token[]{ Token(TABLE_KEYWORDS, 0) }, 0, false, false, false, false));

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 0) }, 1, false, false, false, true)); // 1: Func

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 0) }, 2, true, false, false, true)); // 2: type
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_IDENTIFIERS, -1) }, 3, true, false, false, true)); // 3: identifier
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 6) }, 4, true, false, false, true)); // 4: (
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 7) }, 5, true, false, false, true)); // 5: )
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 4) }, 6, true, false, false, true)); // 6: {
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3), 
																   new Token(TABLE_KEYWORDS, 0), 
		                                                           new Token(TABLE_IDENTIFIERS, -1), 
		                                                           new Token(TABLE_CONSTANTS, -1),
																   new Token(TABLE_DELIMETERS, 6), 
		                                                           new Token(TABLE_KEYWORDS, 1), 
		                                                           new Token(TABLE_KEYWORDS, 2), 
		                                                           new Token(TABLE_DELIMETERS, 5) }, 8, false, true, false, true)); // 7: Body
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 5) }, 0, true, false, true, true)); // 8: }

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3), 
																   new Token(TABLE_KEYWORDS, 0), 
																   new Token(TABLE_IDENTIFIERS, -1), 
																   new Token(TABLE_CONSTANTS, -1),
																   //new Token(TABLE_DELIMETERS, 6), 
																   new Token(TABLE_KEYWORDS, 1), 
																   new Token(TABLE_KEYWORDS, 2) }, 10, false, false, false, false)); // 9: Body1
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 5) }, 12, false, false, false, true)); // 10: Body2

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3), new Token(TABLE_KEYWORDS, 0), new Token(TABLE_IDENTIFIERS, -1), new Token(TABLE_CONSTANTS, -1),
																   new Token(TABLE_DELIMETERS, 6), new Token(TABLE_KEYWORDS, 1), new Token(TABLE_KEYWORDS, 2) }, 13, false, true, false, true)); // 11: Action
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3), new Token(TABLE_KEYWORDS, 0), new Token(TABLE_IDENTIFIERS, -1), new Token(TABLE_CONSTANTS, -1),
																   new Token(TABLE_DELIMETERS, 6), new Token(TABLE_KEYWORDS, 1), new Token(TABLE_KEYWORDS, 2), new Token(TABLE_DELIMETERS, 5) }, 8, false, false, false, true)); // 12: Body

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 5) }, 0, false, false, true, true));  // 13: Empty

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3) }, 18, false, false, false, false)); // 14: Action1
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 0) }, 19, false, false, false, false)); // 15: Action2
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_IDENTIFIERS, -1), new Token(TABLE_CONSTANTS, -1), new Token(TABLE_DELIMETERS, 6) }, 21, false, false, false, false)); // 16: Action3
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 1) }, 23, false, false, false, false)); // 17: Action4
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 2) }, 24, false, false, false, true)); // 18: Action5

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3) }, 0, true, false, true, true)); // 19: ;

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 0) }, 26, false, true, false, true)); // 20: Declaration
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3) }, 0, true, false, true, true)); // 21: ;

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_IDENTIFIERS, -1), new Token(TABLE_CONSTANTS, -1), new Token(TABLE_DELIMETERS, 6) }, 27, false, true, false, true)); // 22: Expression
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3) }, 0, true, false, true, true)); // 23: ;

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 1) }, 30, false, false, false, true)); // 24: While

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 2) }, 31, false, true, false, true)); // 25: DoWhile
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3) }, 0, true, false, true, true)); // 26: ;


	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 0) }, 32, false, false, false, true)); // 27: Declaration1

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_IDENTIFIERS, -1) }, 36, false, false, false, false)); // 28: Expression1
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_CONSTANTS, -1) }, 38, false, false, false, false)); // 29: Expression2
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 6) }, 40, false, false, false, true)); // 30: Expression3

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 1) }, 44, false, false, false, true)); // 31: While1

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 2) }, 49, false, false, false, true)); // 32: DoWhile1

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 0) }, 33, true, false, false, true)); // 33: type
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_IDENTIFIERS, -1) }, 34, true, false, false, true)); // 34: identifier
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 3), new Token(TABLE_DELIMETERS, 8), new Token(TABLE_DELIMETERS, 3) }, 57, false, true, false, true)); // 35: Value
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 8), new Token(TABLE_DELIMETERS, 3) }, 59, false, false, false, true)); // 36: Tail

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_IDENTIFIERS, -1) }, 37, true, false, false, true)); // 37: identifier
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 3), new Token(TABLE_KEYWORDS, 4), new Token(TABLE_KEYWORDS, 5), 
																   new Token(TABLE_KEYWORDS, 6), new Token(TABLE_KEYWORDS, 7), new Token(TABLE_KEYWORDS, 8), 
																   new Token(TABLE_KEYWORDS, 9), new Token(TABLE_KEYWORDS, 10), new Token(TABLE_KEYWORDS, 11), 
																   new Token(TABLE_KEYWORDS, 12), new Token(TABLE_KEYWORDS, 13), new Token(TABLE_DELIMETERS, 3),
																   new Token(TABLE_DELIMETERS, 7) }, 61, false, false, false, true)); // 38: Expression_Tail

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_CONSTANTS, -1) }, 39, true, false, false, true)); // 39: constant
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 4), new Token(TABLE_KEYWORDS, 5), new Token(TABLE_KEYWORDS, 6),
																   new Token(TABLE_KEYWORDS, 7), new Token(TABLE_KEYWORDS, 8), new Token(TABLE_KEYWORDS, 9),
																   new Token(TABLE_KEYWORDS, 12), new Token(TABLE_KEYWORDS, 13), new Token(TABLE_DELIMETERS, 3),
																   new Token(TABLE_DELIMETERS, 7), new Token(TABLE_DELIMETERS, 8) }, 63, false, false, false, true)); // 40: NAExpression_Tail

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 6) }, 41, true, false, false, true)); // 41: (
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_IDENTIFIERS, -1), new Token(TABLE_CONSTANTS, -1), new Token(TABLE_DELIMETERS, 6) }, 27, false, true, false, true)); // 42: Expression
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 7) }, 43, true, false, false, true)); // 43: )
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 3), new Token(TABLE_KEYWORDS, 4), new Token(TABLE_KEYWORDS, 5),
																   new Token(TABLE_KEYWORDS, 6), new Token(TABLE_KEYWORDS, 7), new Token(TABLE_KEYWORDS, 8),
																   new Token(TABLE_KEYWORDS, 9), new Token(TABLE_KEYWORDS, 10), new Token(TABLE_KEYWORDS, 11),
																   new Token(TABLE_KEYWORDS, 12), new Token(TABLE_KEYWORDS, 13), new Token(TABLE_DELIMETERS, 3),
																   new Token(TABLE_DELIMETERS, 7), new Token(TABLE_DELIMETERS, 8) }, 61, false, false, false, true)); // 44: Expression_Tail

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 1) }, 45, true, false, false, true)); // 45: while
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 6) }, 46, true, false, false, true)); // 46: (
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_IDENTIFIERS, -1), new Token(TABLE_CONSTANTS, -1), new Token(TABLE_DELIMETERS, 6) }, 27, false, true, false, true)); // 47: Expression
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 7) }, 48, true, false, false, true)); // 48: )
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 4), new Token(TABLE_DELIMETERS, 3), new Token(TABLE_KEYWORDS, 0), new Token(TABLE_IDENTIFIERS, -1),
																   new Token(TABLE_CONSTANTS, -1), new Token(TABLE_DELIMETERS, 6), new Token(TABLE_KEYWORDS, 1), new Token(TABLE_KEYWORDS, 2) }, 65, false, false, false, true)); // 49: WhileBody

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 2) }, 50, true, false, false, true)); // 50: do
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 4) }, 51, true, false, false, true)); // 51: {
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3), new Token(TABLE_KEYWORDS, 0), new Token(TABLE_IDENTIFIERS, -1), new Token(TABLE_CONSTANTS, -1),
																   new Token(TABLE_DELIMETERS, 6), new Token(TABLE_KEYWORDS, 1), new Token(TABLE_KEYWORDS, 2), new Token(TABLE_KEYWORDS, 3), new Token(TABLE_DELIMETERS, 5) }, 8, false, false, false, true)); // 52: Body
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 5) }, 53, true, false, false, true)); // 53: }
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 2) }, 54, true, false, false, true)); // 54: while
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 6) }, 55, true, false, false, true)); // 55: (
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_IDENTIFIERS, -1), new Token(TABLE_CONSTANTS, -1), new Token(TABLE_DELIMETERS, 6) }, 56, false, true, false, true)); // 56: Expression
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 7) }, 0, true, false, true, true)); // 57: )


	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 3) }, 67, false, false, false, false)); // 58: Value1
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 8), new Token(TABLE_DELIMETERS, 3) }, 69, false, false, false, true)); // 59: Value2

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 8) }, 70, false, false, false, false)); // 60: Tail1
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3) }, 74, false, false, false, true)); // 61: Tail2

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 3), new Token(TABLE_KEYWORDS, 4), new Token(TABLE_KEYWORDS, 5), new Token(TABLE_KEYWORDS, 6), 
																   new Token(TABLE_KEYWORDS, 7), new Token(TABLE_KEYWORDS, 8), new Token(TABLE_KEYWORDS, 9), new Token(TABLE_KEYWORDS, 10), 
																   new Token(TABLE_KEYWORDS, 11), new Token(TABLE_KEYWORDS, 12), new Token(TABLE_KEYWORDS, 13) }, 75, false, false, false, false)); // 62: Expression_Tail1
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 7), new Token(TABLE_DELIMETERS, 3), new Token(TABLE_DELIMETERS, 8) }, 77, false, false, false, true)); // 63: Expression_Tail2

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 4), new Token(TABLE_KEYWORDS, 5), new Token(TABLE_KEYWORDS, 6), new Token(TABLE_KEYWORDS, 7), 
																   new Token(TABLE_KEYWORDS, 8), new Token(TABLE_KEYWORDS, 11), new Token(TABLE_KEYWORDS, 12), new Token(TABLE_KEYWORDS, 13) }, 78, false, false, false, false)); // 64: NAExpression_Tail1
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 7), new Token(TABLE_DELIMETERS, 3), new Token(TABLE_DELIMETERS, 8) }, 80, false, false, false, true)); // 65: NAExpression_Tail2

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 0), new Token(TABLE_DELIMETERS, 3), new Token(TABLE_IDENTIFIERS, -1), new Token(TABLE_CONSTANTS, -1), new Token(TABLE_KEYWORDS, 1), new Token(TABLE_KEYWORDS, 2) }, 84, false, false, false, false)); // 66: WhileBody1
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 4) }, 81, false, false, false, true)); // 67: WhileBody2

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 3) }, 68, true, false, false, true)); // 68: =
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_IDENTIFIERS, -1), new Token(TABLE_CONSTANTS, -1), new Token(TABLE_DELIMETERS, 6)  }, 27, false, false, false, true)); // 69: Expression

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 8), new Token(TABLE_DELIMETERS, 3) }, 0, false, false, true, true)); // 70: Empty

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 8) }, 71, true, false, false, true)); // 71: ,
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_IDENTIFIERS, -1) }, 72, true, false, false, true)); // 72: identifier
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3), new Token(TABLE_DELIMETERS, 8), new Token(TABLE_KEYWORDS, 3) }, 57, false, true, false, true)); // 73: Value
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3), new Token(TABLE_DELIMETERS, 8) }, 59, false, false, false, true)); // 74: Tail

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3), new Token(TABLE_DELIMETERS, 8) }, 0, false, false, true, true)); // 75: Empty

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 3), new Token(TABLE_KEYWORDS, 4), new Token(TABLE_KEYWORDS, 5),
																   new Token(TABLE_KEYWORDS, 6), new Token(TABLE_KEYWORDS, 7), new Token(TABLE_KEYWORDS, 8),
																   new Token(TABLE_KEYWORDS, 9), new Token(TABLE_KEYWORDS, 10), new Token(TABLE_KEYWORDS, 11),
																   new Token(TABLE_KEYWORDS, 12), new Token(TABLE_KEYWORDS, 13) }, 85, false, true, false, true)); // 76: Operation
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_IDENTIFIERS, -1), new Token(TABLE_CONSTANTS, -1), new Token(TABLE_DELIMETERS, 6) }, 27, false, false, false, true)); // 77: Expression

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3), new Token(TABLE_DELIMETERS, 7), new Token(TABLE_DELIMETERS, 8) }, 0, false, false, true, true)); // 78: Empty

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 3), new Token(TABLE_KEYWORDS, 4), new Token(TABLE_KEYWORDS, 5),
																   new Token(TABLE_KEYWORDS, 6), new Token(TABLE_KEYWORDS, 7) }, 96, false, true, false, true)); // 79: NAOperation
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_IDENTIFIERS, -1), new Token(TABLE_CONSTANTS, -1), new Token(TABLE_DELIMETERS, 6) }, 27, false, false, false, true)); // 80: Expression

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 7), new Token(TABLE_DELIMETERS, 3), new Token(TABLE_DELIMETERS, 8) }, 0, false, false, true, true)); // 81: Empty

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 4) }, 82, true, false, false, true)); // 82: {
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3), new Token(TABLE_KEYWORDS, 0), new Token(TABLE_IDENTIFIERS, -1), new Token(TABLE_CONSTANTS, -1),
																   new Token(TABLE_DELIMETERS, 6), new Token(TABLE_KEYWORDS, 1), new Token(TABLE_KEYWORDS, 2), new Token(TABLE_DELIMETERS, 5) }, 8, false, true, false, true)); // 83: Body
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 5) }, 0, true, false, true, true)); // 84: }

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_DELIMETERS, 3), new Token(TABLE_KEYWORDS, 0), new Token(TABLE_IDENTIFIERS, -1), 
																   new Token(TABLE_CONSTANTS, -1), new Token(TABLE_KEYWORDS, 1), new Token(TABLE_KEYWORDS, 2) }, 13, false, false, false, true)); // 85: Action

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 3) }, 104, false, false, false, false)); // 86: Operation1
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 4) }, 105, false, false, false, false)); // 87: Operation2
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 5) }, 106, false, false, false, false)); // 88: Operation3
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 6) }, 107, false, false, false, false)); // 89: Operation4
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 7) }, 108, false, false, false, false)); // 90: Operation5
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 8) }, 119, false, false, false, false)); // 91: Operation6
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 9) }, 110, false, false, false, false)); // 92: Operation7
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 10) }, 111, false, false, false, false)); // 93: Operation8
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 11) }, 112, false, false, false, false)); // 94: Operation9
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 12) }, 113, false, false, false, false)); // 95: Operation10
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 13) }, 114, false, false, false, true)); // 96: Operation11

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 4) }, 115, false, false, false, false)); // 97: NAOperation1
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 5) }, 116, false, false, false, false)); // 98: NAOperation2
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 6) }, 117, false, false, false, false)); // 99: NAOperation3
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 7) }, 118, false, false, false, false)); // 100: NAOperation4
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 8) }, 119, false, false, false, false)); // 101: NAOperation5
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 11) }, 120, false, false, false, false)); // 102: NAOperation6
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 12) }, 121, false, false, false, false)); // 103: NAOperation7
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 13) }, 122, false, false, false, true)); // 104: NAOperation8

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 3) }, 0, true, false, true, true)); // 105: =
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 4) }, 0, true, false, true, true)); // 106: +
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 5) }, 0, true, false, true, true)); // 107: -
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 6) }, 0, true, false, true, true)); // 108: <
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 7) }, 0, true, false, true, true)); // 109: >
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 8) }, 0, true, false, true, true)); // 110: ==
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 9) }, 0, true, false, true, true)); // 111: +=
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 10) }, 0, true, false, true, true)); // 112: -=
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 11) }, 0, true, false, true, true)); // 113: <
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 12) }, 0, true, false, true, true)); // 114: >
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 13) }, 0, true, false, true, true)); // 115: !=

	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 4) }, 0, true, false, true, true)); // 116: +
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 5) }, 0, true, false, true, true)); // 117: -
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 6) }, 0, true, false, true, true)); // 118: <
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 7) }, 0, true, false, true, true)); // 119: >
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 8) }, 0, true, false, true, true)); // 120: ==
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 11) }, 0, true, false, true, true)); // 121: <
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 12) }, 0, true, false, true, true)); // 122: >
	parsingTable->add(new ParsingTable_Record(std::vector<Token*>{ new Token(TABLE_KEYWORDS, 13) }, 0, true, false, true, true)); // 123: !=
}

ParsingTree* parse(std::vector<Token*>* tokens, std::stack<std::pair<int, ParsingTree*>>* stack, Error** out_error)
{
	ParsingTree* root = new ParsingTree(0, nullptr, nullptr);
	ParsingTree* curTree = root;

	int curState = 0;
	Token* curToken;
	bool isLeft = true;
	while (true)
	{
		if (tokens->size() == 0)
		{
			*out_error = new Error("", 0, 0, "Unexpected end of file.");
			return nullptr;
		}
		curToken = (*tokens)[0];

		ParsingTable_Record* record = Translator::parsingTable->get(curState);
		int i;
		for (i = 0; i < record->terminals.size(); i++)
			if (record->terminals[i]->table_id == curToken->table_id && (record->terminals[i]->record_id == -1 || record->terminals[i]->record_id == curToken->record_id))
				break;
		if (i == record->terminals.size())
		{
			if (record->error)
			{
				*out_error = new Error("", 0, 0, "Unexpected symbol");
				return nullptr;
			}
			else
			{
				curState++;
				continue;
			}
		}

		if (record->stack)
			stack->push(std::pair<int, ParsingTree*>(curState + 1, curTree));

		if (record->accept)
		{
			if (curToken->table_id == TABLE_IDENTIFIERS && curTree->state == 0)
				Translator::identifiers->get(curToken->record_id)->identifierType = IdentifierType::FUNCTION;
			curTree->add(new ParsingTree(curState, curToken, curTree));
			tokens->erase(tokens->begin());
		}
		else
		{
			if (record->jump > 0)
			{
				if (!isLeft)
				{
					ParsingTree* leaf = new ParsingTree(curState, nullptr, curTree);
					curTree->add(leaf);
					curTree = leaf;
				}
				isLeft = !isLeft;
				curTree->state = curState;
			}
		}

		if (record->jump > 0)
			curState = record->jump;

		if (record->ret)
		{
			if (stack->empty())
				break;

			curTree = stack->top().second;
			curState = stack->top().first;
			stack->pop();
		}
	}
	return root;
}

//keywords->add(new Record_Keywords("=")); 3
//keywords->add(new Record_Keywords("+")); 4
//keywords->add(new Record_Keywords("-")); 5
//keywords->add(new Record_Keywords("<")); 6
//keywords->add(new Record_Keywords(">")); 7
//keywords->add(new Record_Keywords("==")); 8
//keywords->add(new Record_Keywords("+=")); 9
//keywords->add(new Record_Keywords("-=")); 10
//keywords->add(new Record_Keywords("<=")); 11
//keywords->add(new Record_Keywords(">=")); 12
//keywords->add(new Record_Keywords("!=")); 13

int getOperatorPriority(int record_id, bool* out_isLeftAssociative)
{
	*out_isLeftAssociative = true;
	switch (record_id)
	{
	case 3:
	case 9:
	case 10:
		*out_isLeftAssociative = false;
		return 0;
	case 6:
	case 7:
	case 8:
	case 11:
	case 12:
	case 13:
		return 1;
	case 4:
	case 5:
		return 2;
	}
}

Error* _getPostfix(ParsingTree* tree, std::vector<Token*>* result, std::stack<Token*>* stack)
{
	if (tree->token != nullptr)
	{
		switch (tree->token->table_id)
		{
		case TABLE_KEYWORDS:
		{
			int curPriority, stackPriority;
			bool isLeftAssotiative;
			curPriority = getOperatorPriority(tree->token->record_id, &isLeftAssotiative);
			while (stack->size() > 0)
			{
				stackPriority = getOperatorPriority(stack->top()->record_id, &isLeftAssotiative);
				if (stackPriority > curPriority || (stackPriority == curPriority && isLeftAssotiative))
				{
					result->push_back(stack->top());
					stack->pop();
				}
				else
					break;
			}
			stack->push(tree->token);
			break;
		}
		case TABLE_DELIMETERS:
		{
			switch (tree->token->record_id)
			{
			case 6: // (
				stack->push(tree->token);
				break;
			case 7: // )
				while (stack->top()->table_id != TABLE_DELIMETERS || stack->top()->record_id != 6)
				{
					result->push_back(stack->top());
					stack->pop();
				}
				stack->pop();
				break;
			}
			break;
		}
		case TABLE_IDENTIFIERS:
		{
			Record_Identifiers* record = Translator::identifiers->get(tree->token->record_id);
			if (!record->declared)
			{
				char* message = (char*)calloc(strlen(record->name) + MESSAGE_LEN, sizeof(char));
				sprintf_s(message, strlen(record->name) + MESSAGE_LEN, "%s: identifier is not declared.", record->name);
				return new Error("", 0, 0, message);
			}
			result->push_back(tree->token);
			break;
		}
		case TABLE_CONSTANTS:
		{
			result->push_back(tree->token);
			break;
		}
		}
	}
	for (int i = 0; i < tree->leaves->size(); i++)
	{
		Error* error = _getPostfix(tree->leaves->at(i), result, stack);
		if (error != nullptr)
			return error;
	}
	return nullptr;
}

void printToken(Token* token)
{
	switch (token->table_id)
	{
	case 0:
		printf("%s ", Translator::keywords->get(token->record_id)->keyword);
		break;
	case 1:
		printf("%c ", Translator::delimeters->get(token->record_id)->symbol);
		break;
	case 2:
		printf("%s ", Translator::identifiers->get(token->record_id)->name);
		break;
	case 3:
		printf("%d ", *(int*)Translator::constants->get(token->record_id)->value);
		break;
	}
}

Error* getExpressionTree(ParsingTree* tree, ExpressionTree** out_expressionTree)
{
	std::vector<Token*> postfix = std::vector<Token*>();
	std::stack<Token*> tokenStack = std::stack<Token*>();
	Error* error = _getPostfix(tree, &postfix, &tokenStack);
	if (error != nullptr)
		return error;
	while (tokenStack.size() > 0)
	{
		postfix.push_back(tokenStack.top());
		tokenStack.pop();
	}

	std::stack<ExpressionTree*> expressionStack = std::stack<ExpressionTree*>();
	for (auto iter : postfix)
	{
		if (iter->table_id == TABLE_KEYWORDS)
		{
			ExpressionTree* tree = new ExpressionTree(iter);
			tree->right = expressionStack.top();
			expressionStack.pop();
			tree->left = expressionStack.top();
			expressionStack.pop();
			expressionStack.push(tree);
			if (iter->record_id == 3 || iter->record_id == 8 || iter->record_id == 9)
			{
				if (tree->left->token->table_id != 2)
					return new Error("", 0, 0, "Expression must be modifiable.");
				Translator::identifiers->get(tree->left->token->record_id)->initialized = true;
			}

			char* message = (char*)calloc(MESSAGE_LEN, sizeof(char));
			if (tree->right->token->table_id == TABLE_IDENTIFIERS && !Translator::identifiers->get(tree->right->token->record_id)->initialized)
			{
				sprintf_s(message, MESSAGE_LEN, "%s: variable is not initialized.\0", Translator::identifiers->get(tree->right->token->record_id)->name);
				return new Error("", 0, 0, message);
			}
			if (tree->left->token->table_id == TABLE_IDENTIFIERS && !Translator::identifiers->get(tree->left->token->record_id)->initialized)
			{
				sprintf_s(message, MESSAGE_LEN, "%s : variable is not initialized.\0", Translator::identifiers->get(tree->left->token->record_id)->name);
				return new Error("", 0, 0, message);
			}
		}
		else
			expressionStack.push(new ExpressionTree(iter));
	}
	*out_expressionTree = expressionStack.top();
	expressionStack.pop();
	return nullptr;
}

Error* checkLogicErrors(ParsingTree* tree)
{
	if (tree->state == 26 || tree->state == 59) // Declaration or Tail
	{
		Record_Identifiers* record = Translator::identifiers->get(tree->leaves->at(1)->token->record_id);
		if (record->declared)
		{
			char* message = (char*)calloc(MESSAGE_LEN, sizeof(char));
			sprintf_s(message, MESSAGE_LEN, "%s: identifier is already declared.\0", record->name);
			return new Error("", 0, 0, message);
		}
		record->declared = true;
		if (tree->leaves->at(2)->leaves->size() > 0)
		{
			ParsingTree* expr = new ParsingTree(27, nullptr, nullptr);
			ParsingTree* ident = new ParsingTree(36, tree->leaves->at(1)->token, expr);
			ParsingTree* exprTail = new ParsingTree(61, nullptr, expr);
			ParsingTree* oper = new ParsingTree(85, nullptr, exprTail);
			ParsingTree* eq = new ParsingTree(104, tree->leaves->at(2)->leaves->at(0)->token, oper);
			expr->add(ident);
			expr->add(exprTail);
			exprTail->add(oper);
			exprTail->add(tree->leaves->at(2)->leaves->at(1));
			oper->add(eq);

			Error* error = checkLogicErrors(expr);
			if (error != nullptr)
				return error;
			delete expr;
			delete ident;
			delete exprTail;
			delete oper;
			delete eq;

			record->initialized = true;
		}
		if (tree->leaves->at(3)->leaves->size() > 0)
			return checkLogicErrors(tree->leaves->at(3));
		return nullptr;
	}
	if (tree->state >= 27 && tree->state <= 29) // Expression
	{
		ExpressionTree* exprTree;
		Error* error = getExpressionTree(tree, &exprTree);
		if (error != nullptr)
			return error;

		// printing infix and postfix notations of each expression
		//std::vector<Token*>* result = exprTree->getInfix();
		//for (auto token : *result)
		//	printToken(token);
		//delete result;
		//
		//printf("\n");
		//
		//result = exprTree->getPostfix();
		//for (auto token : *result)
		//	printToken(token);
		//delete result;

		return nullptr;
	}
	for (int i = 0; i < tree->leaves->size(); i++)
	{
		Error* error = checkLogicErrors(tree->leaves->at(i));
		if (error != nullptr)
			return error;
	}
	return nullptr;
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

	std::stack<std::pair<int, ParsingTree*>>* stack = new std::stack<std::pair<int, ParsingTree*>>();
	Error* error = nullptr;
	ParsingTree* tree = parse(&tokens, stack, &error);
	delete stack;
	if (error != nullptr)
		return error;
	error = checkLogicErrors(tree);
	if (error != nullptr)
		return error;

	

	//for (auto token : tokens)
	//{
	//	if (token->table_id == 1)
	//	{
	//		if (token->record_id == 1)
	//			fprintf_s(file_out, "\n");
	//		else if (token->record_id == 2)
	//			fprintf_s(file_out, "\t");
	//		else
	//			fprintf_s(file_out, "(%d,%d)", token->table_id, token->record_id);
	//	}
	//	else
	//		fprintf_s(file_out, "(%d,%d)", token->table_id, token->record_id);
	//}

	fprintf_s(file_out, ".386\n.model flat, stdcall\n.data\n");

	for (auto iter : *identifiers)
	{
		if (iter->identifierType != IdentifierType::VARIABLE)
			continue;
		fprintf_s(file_out, "%s dword ?\n", iter->name);
	}

	fprintf_s(file_out, ".code\n");

	fprintf_s(file_out, "end main");

	fclose(file_in);
	fclose(file_out);
	return nullptr;
}