#pragma once
#include <stdio.h>
#include "Table_Keywords.h"
#include "Table_TerminalSymbols.h"
#include "Table_Identifiers.h"
#include "Table_Constants.h"
#include "Token.h"

Table_Keywords* keywords;
Table_TerminalSymbols* terminalSymbols;
Table_Identifiers* identifiers;
Table_Constants* constants;

const int MAX_IDENTIFIER_LENGTH = 2049;

class Translator
{
public:
	static void Init();
	static bool TranslateFile(const char* pathFrom, const char* pathTo);
};

