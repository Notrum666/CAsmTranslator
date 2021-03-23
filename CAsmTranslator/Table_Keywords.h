#pragma once
#include <vector>

struct Record_Keywords
{
public:
	const char* keyword;
	Record_Keywords(const char* keyword);
};

class Table_Keywords
{
private:
	std::vector<Record_Keywords*> records;
public:
	Table_Keywords();
	int add(Record_Keywords* record);
	Record_Keywords* get(int id);
	Record_Keywords* getByKeyword(const char* keyword);
	int getId(Record_Keywords* record);
	int getIdByKeyword(const char* keyword);
	void print();
};