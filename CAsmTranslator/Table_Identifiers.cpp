#include "Table_Identifiers.h"

Record_Identifiers::Record_Identifiers(const char* name, void* value, Type type)
{
	this->name = name;
	this->value = value;
	this->type = type;
	initialized = false;
}

Table_Identifiers::Table_Identifiers()
{
	records = std::vector<Record_Identifiers*>();
}

int Table_Identifiers::add(Record_Identifiers* record)
{
	records.push_back(record);
	return records.size() - 1;
}

Record_Identifiers* Table_Identifiers::get(int id)
{
	return records[id];
}

Record_Identifiers* Table_Identifiers::getByName(const char* name)
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

int Table_Identifiers::getIdByName(const char* name)
{
	int size = records.size();
	for (int i = 0; i < size; i++)
		if (!std::strcmp(records[i]->name, name))
			return i;
	return -1;
}

void Table_Identifiers::print()
{
	printf_s("Identifiers table:\n");
	for (int i = 0; i < records.size(); i++)
		printf_s("%d. %s %s %d %d\n", i, records[i]->name, "int", records[i]->value, records[i]->initialized);
}