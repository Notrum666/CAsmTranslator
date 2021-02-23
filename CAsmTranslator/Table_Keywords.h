#pragma once
#include <vector>

struct Record_Keywords_str
{
public:
	char* keyword;
	Record_Keywords_str(char* keyword);
} typedef Record_Keywords;

class Table_Keywords
{
private:
	std::vector<Record_Keywords*> records;
public:
	Table_Keywords();
	void add(Record_Keywords* record);
	Record_Keywords* get(int id);
	Record_Keywords* getByKeyword(char* keyword);
	int getId(Record_Keywords* record);
	int getIdByKeyword(char* keyword);
};