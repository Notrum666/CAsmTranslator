#include <vector>
#pragma once

template<typename T>
struct Record_Constants
{
public:
	 T value;
};

template<typename T>
class Table_Constants
{
private:
	std::vector<Record_Constants<T>*> records;
public:
	Table_Constants();
	void add(Record_Constants<T>* record);
	Record_Constants<T>* get(int id);
	Record_Constants<T>* getByValue(T value);
	int getId(Record_Constants<T>* record);
	int getIdByValue(T value);
};

