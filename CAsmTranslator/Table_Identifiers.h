#pragma once
#include <vector>

struct Record_Identifiers_str
{
public:
	char* name;
	bool initialized;
	Record_Identifiers_str(char* name);
} typedef Record_Identifiers;

class Table_Identifiers
{
private:
	std::vector<Record_Identifiers*> records;
public:
	Table_Identifiers();
	void add(Record_Identifiers* record);
	Record_Identifiers* get(int id);
	Record_Identifiers* getByName(char* keyword);
	int getId(Record_Identifiers* record);
	int getIdByName(char* keyword);
};