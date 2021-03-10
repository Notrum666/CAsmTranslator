#pragma once
#include <vector>

struct Record_TerminalSymbols
{
public:
	char symbol;
	bool skip;
	Record_TerminalSymbols(char symbol, bool skip);
};

class Table_TerminalSymbols
{
private:
	std::vector<Record_TerminalSymbols*> records;
public:
	Table_TerminalSymbols();
	int add(Record_TerminalSymbols* record);
	Record_TerminalSymbols* get(int id);
	Record_TerminalSymbols* getBySymbol(char symbol);
	int getId(Record_TerminalSymbols* record);
	int getIdBySymbol(char symbol);
	void print();
};