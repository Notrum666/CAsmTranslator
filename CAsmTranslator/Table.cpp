#include "Table.h"

Table_Keywords::Table_Keywords()
{
	records = std::vector<Record_Keywords*>();
}

void Table_Keywords::add(Record_Keywords* record)
{

}

Record_Keywords* Table_Keywords::get(int id)
{
	return records[id];
}

Record_Keywords* Table_Keywords::getByKeyword(char* keyword)
{
	for (auto record : records)
		if (!std::strcmp(record->keyword, keyword))
			return record;
	return nullptr;
}

int Table_Keywords::getId(Record_Keywords* record)
{
	int size = records.size();
	for (int i = 0; i < size; i++)
		if (!std::strcmp(records[i]->keyword, record->keyword))
			return i;
	return -1;
}

int Table_Keywords::getIdByKeyword(char* keyword)
{
	int size = records.size();
	for (int i = 0; i < size; i++)
		if (!std::strcmp(records[i]->keyword, keyword))
			return i;
	return -1;
}