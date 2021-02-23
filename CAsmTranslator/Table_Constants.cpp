#include "Table_Constants.h"
#include <vector>

template<typename T>
Table_Constants<T>::Table_Constants()
{
	records = std::vector<Table_Constants<T>*>();
}

template<typename T>
void Table_Constants<T>::add(Record_Constants<T>* record)
{
	records.push_back(record);
}

template<typename T>
Record_Constants<T>* Table_Constants<T>::get(int id)
{
	return records[id];
}

template<typename T>
Record_Constants<T>* Table_Constants<T>::getByValue(T value)
{
	if (std::is_same<T, char*>::value)
	{
		for (auto record : records)
			if (!std::strcmp(record->value, value))
				return record;
	}
	else
	{
		for (auto record : records)
			if (record->value == value)
				return record;
	}
	return nullptr;
}

template<typename T>
int Table_Constants<T>::getId(Record_Constants<T>* record)
{
	int size = records.size();
	if (std::is_same<T, char*>::value)
	{
		for (int i = 0; i < size; i++)
			if (!std::strcmp(records[i]->value, record))
				return i;
	}
	else
	{
		for (int i = 0; i < size; i++)
			if (records[i]->value == record)
				return i;
	}	
	return -1;
}

template<typename T>
int Table_Constants<T>::getIdByValue(T value)
{
	if (std::is_same<T, char*>::value)
	{
		for (int i = 0; i < size; i++)
			if (!std::strcmp(records[i]->value, value))
				return i;
	}
	else
	{
		for (int i = 0; i < size; i++)
			if (records[i]->value == value)
				return i;
	}
	return -1;
}