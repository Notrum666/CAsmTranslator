#include "Table_Delimeters.h"

Record_Delimeters::Record_Delimeters(char symbol, bool skip)
{
	this->symbol = symbol;
	this->skip = skip;
}

Table_Delimeters::Table_Delimeters()
{
	records = std::vector<Record_Delimeters*>();
}

int Table_Delimeters::add(Record_Delimeters* record)
{
	records.push_back(record);
	return records.size() - 1;
}

Record_Delimeters* Table_Delimeters::get(int id)
{
	return records[id];
}

Record_Delimeters* Table_Delimeters::getBySymbol(const char symbol)
{
	for (auto record : records)
		if (record->symbol == symbol)
			return record;
	return nullptr;
}

int Table_Delimeters::getId(Record_Delimeters* record)
{
	int size = records.size();
	for (int i = 0; i < size; i++)
		if (records[i]->symbol == record->symbol)
			return i;
	return -1;
}

int Table_Delimeters::getIdBySymbol(const char symbol)
{
	int size = records.size();
	for (int i = 0; i < size; i++)
		if (records[i]->symbol == symbol)
			return i;
	return -1;
}

void Table_Delimeters::print()
{
	printf_s("Terminal symbols table:\n");
	int i;
	for (i = 0; i < records.size(); i++)
		printf_s("%d. %c %d\n", i, (char*)records[i]->symbol, records[i]->skip);
}