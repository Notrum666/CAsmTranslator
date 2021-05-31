#pragma once
#include <vector>
#include "Types.h"

struct Record_Identifiers
{
public:
	const char* name;
	ValueType valueType;
	IdentifierType identifierType;
	bool declared;
	bool initialized;
	Record_Identifiers(const char* name, ValueType valueType);
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
	std::vector<Record_Identifiers*>::iterator begin();
	std::vector<Record_Identifiers*>::iterator end();
	std::vector<Record_Identifiers*>::const_iterator begin() const;
	std::vector<Record_Identifiers*>::const_iterator end() const;
	void print();
};