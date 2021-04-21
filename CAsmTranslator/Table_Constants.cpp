#include "Table_Constants.h"
#include <vector>

Record_Constants::Record_Constants(void* value, Type type)
{
	this->value = value;
	this->type = type;
}

Table_Constants::Table_Constants()
{
	records = std::vector<Record_Constants*>();
}

int Table_Constants::add(Record_Constants* record)
{
	records.push_back(record);
	return records.size() - 1;
}

Record_Constants* Table_Constants::get(int id)
{
	return records[id];
}

Record_Constants* Table_Constants::getByValue(void* value)
{
	for (auto record : records)
		if (equal(record->value, value, record->type))
			return record;
	return nullptr;
}

int Table_Constants::getId(Record_Constants* record)
{
	int size = records.size();
	for (int i = 0; i < size; i++)
		if (records[i] == record)
			return i;
	return -1;
}

int Table_Constants::getIdByValue(void* value)
{
	int size = records.size();
	for (int i = 0; i < size; i++)
		if (equal(records[i]->value, value, records[i]->type))
			return i;
	return -1;
}

void Table_Constants::print()
{
	printf_s("Constants table:\n");
	int i;
	for (i = 0; i < records.size(); i++)
		printf_s("%d. %d %s\n", i, *((int*)records[i]->value), "int");
}