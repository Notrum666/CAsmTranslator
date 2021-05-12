#pragma once
#include <stdio.h>
#include <string.h>
#include <regex>
#include <stack>
#include "StateGraph.h"
#include "Table_Keywords.h"
#include "Table_Delimeters.h"
#include "Table_Identifiers.h"
#include "Table_Constants.h"
#include "ParsingTable.h"
#include "ParsingTree.h"
#include "ExpressionTree.h"
#include "Error.h"

class Translator
{
public:
	static Table_Keywords* keywords;
	static Table_Delimeters* delimeters;
	static Table_Identifiers* identifiers;
	static Table_Constants* constants;
	static ParsingTable* parsingTable;
	static const int MAX_IDENTIFIER_LENGTH = 2049;

	static void Init();
	static Error* TranslateFile(const char* pathFrom, const char* pathTo);
};

