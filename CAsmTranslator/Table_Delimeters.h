#pragma once
#include <vector>

struct Record_Delimeters
{
public:
	char symbol;
	bool skip;
	Record_Delimeters(char symbol, bool skip);
};

class Table_Delimeters
{
private:
	std::vector<Record_Delimeters*> records;
public:
	Table_Delimeters();
	int add(Record_Delimeters* record);
	Record_Delimeters* get(int id);
	Record_Delimeters* getBySymbol(const char symbol);
	int getId(Record_Delimeters* record);
	int getIdBySymbol(const char symbol);
	void print();
};