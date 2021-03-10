#pragma once
#include <stdio.h>
#include "Table_Keywords.h"
#include "Table_TerminalSymbols.h"
#include "Table_Identifiers.h"
#include "Table_Constants.h"
#include "Token.h"

enum State
{
	Start = 0,
	Digit = 1,
	Letter = 2,
	Slash = 3
};

class Translator
{
private:
	Table_Keywords* keywords;
	Table_TerminalSymbols* terminalSymbols;
	Table_Identifiers* identifiers;
	Table_Constants* constants;

	const int MAX_IDENTIFIER_LENGTH = 2049;
public:
	Translator();
	bool translateFile(const char* pathFrom, const char* pathTo);
private:
	Token* generateToken(char* text);
};

