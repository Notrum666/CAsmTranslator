#include "Table_TerminalSymbols.h"

Record_TerminalSymbols::Record_TerminalSymbols(char symbol, bool skip)
{
	this->symbol = symbol;
	this->skip = skip;
}

Table_TerminalSymbols::Table_TerminalSymbols()
{
	records = std::vector<Record_TerminalSymbols*>();
}

int Table_TerminalSymbols::add(Record_TerminalSymbols* record)
{
	records.push_back(record);
	return records.size() - 1;
}

Record_TerminalSymbols* Table_TerminalSymbols::get(int id)
{
	return records[id];
}

Record_TerminalSymbols* Table_TerminalSymbols::getBySymbol(char symbol)
{
	for (auto record : records)
		if (record->symbol == symbol)
			return record;
	return nullptr;
}

int Table_TerminalSymbols::getId(Record_TerminalSymbols* record)
{
	int size = records.size();
	for (int i = 0; i < size; i++)
		if (records[i]->symbol == record->symbol)
			return i;
	return -1;
}

int Table_TerminalSymbols::getIdBySymbol(char symbol)
{
	int size = records.size();
	for (int i = 0; i < size; i++)
		if (records[i]->symbol == symbol)
			return i;
	return -1;
}

void Table_TerminalSymbols::print()
{
	printf_s("Terminal symbols table:\n");
	for (auto record : records)
		printf_s("%c %d\n", (char*)record->symbol, record->skip);
}