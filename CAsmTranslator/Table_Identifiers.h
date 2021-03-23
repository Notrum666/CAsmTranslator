#pragma once
#include <vector>
#include "Types.h"

struct Record_Identifiers
{
public:
	const char* name;
	Type type;
	void* value;
	bool initialized;
	Record_Identifiers(const char* name, void* value, Type type);
};

class Table_Identifiers
{
private:
	std::vector<Record_Identifiers*> records;
public:
	Table_Identifiers();
	int add(Record_Identifiers* record);
	Record_Identifiers* get(int id);
	Record_Identifiers* getByName(const char* keyword);
	int getId(Record_Identifiers* record);
	int getIdByName(const char* keyword);
	void print();
};