#include "Table_Keywords.h"

Record_Keywords::Record_Keywords(const char* keyword)
{
	this->keyword = keyword;
}

Table_Keywords::Table_Keywords()
{
	records = std::vector<Record_Keywords*>();
}

int Table_Keywords::add(Record_Keywords* record)
{
	records.push_back(record);
	return records.size() - 1;
}

Record_Keywords* Table_Keywords::get(int id)
{
	return records[id];
}

Record_Keywords* Table_Keywords::getByKeyword(const char* keyword)
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

int Table_Keywords::getIdByKeyword(const char* keyword)
{
	int size = records.size();
	for (int i = 0; i < size; i++)
		if (!std::strcmp(records[i]->keyword, keyword))
			return i;
	return -1;
}

void Table_Keywords::print()
{
	printf_s("Keywords table:\n");
	for (int i = 0; i < records.size(); i++)
		printf_s("%d. %s\n", i, records[i]->keyword);
}