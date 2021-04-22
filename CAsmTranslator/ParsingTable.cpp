#include "ParsingTable.h"

ParsingTable_Record::ParsingTable_Record(Token* terminals, int jump, bool accept, bool stack, bool ret, bool error)
{
	this->terminals = terminals;
	this->jump = jump;
	this->accept = accept;
	this->stack = stack;
	this->ret = ret;
	this->error = error;
}

ParsingTable::ParsingTable()
{
	records = std::vector<ParsingTable_Record*>();
}

void ParsingTable::add(ParsingTable_Record* record)
{
	records.push_back(record);
}

ParsingTable_Record* ParsingTable::get(int id)
{
	return records[id];
}