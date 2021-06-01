#pragma once
#include <vector>
#include "Types.h"

struct Record_Constants
{
public:
	void* value;
	ValueType type;
	Record_Constants(void* value, ValueType type);
	char* getString();
};

class Table_Constants
{
private:
	std::vector<Record_Constants*> records;
public:
	Table_Constants();
	int add(Record_Constants* record);
	Record_Constants* get(int id);
	Record_Constants* getByValue(void* value);
	int getId(Record_Constants* record);
	int getIdByValue(void* value);
	void print();
};

