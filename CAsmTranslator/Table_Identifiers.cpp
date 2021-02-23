#include "Table_Identifiers.h"

Record_Identifiers::Record_Identifiers_str(char* name)
{
	this->name = name;
	initialized = false;
}

Table_Identifiers::Table_Identifiers()
{
	records = std::vector<Record_Identifiers*>();
}

void Table_Identifiers::add(Record_Identifiers* record)
{
	records.push_back(record);
}

Record_Identifiers* Table_Identifiers::get(int id)
{
	return records[id];
}

Record_Identifiers* Table_Identifiers::getByName(char* name)
{
	for (auto record : records)
		if (!std::strcmp(record->name, name))
			return record;
	return nullptr;
}

int Table_Identifiers::getId(Record_Identifiers* record)
{
	int size = records.size();
	for (int i = 0; i < size; i++)
		if (!std::strcmp(records[i]->name, record->name))
			return i;
	return -1;
}

int Table_Identifiers::getIdByName(char* name)
{
	int size = records.size();
	for (int i = 0; i < size; i++)
		if (!std::strcmp(records[i]->name, name))
			return i;
	return -1;
}