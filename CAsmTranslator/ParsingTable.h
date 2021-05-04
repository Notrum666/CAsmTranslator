#pragma once
#include "Token.h"
#include <vector>
#include "ParsingRule.h"
#include <queue>

struct ParsingTable_Record
{
	Token* terminals;
	int jump;
	bool accept, stack, ret, error;
	ParsingTable_Record(Token* terminals, int jump, bool accept, bool stack, bool ret, bool error);
};

class ParsingTable
{
private:
	std::vector<ParsingTable_Record*>* records;
public:
	ParsingTable();
	ParsingTable(std::vector<ParsingTable_Record*>* records);
	void add(ParsingTable_Record* record);
	ParsingTable_Record* get(int id);
};

