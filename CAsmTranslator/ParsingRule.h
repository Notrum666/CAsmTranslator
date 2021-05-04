#pragma once
#include <vector>

struct ParsingRule
{
	const char* leftPart;
	std::vector<const char*>* rightPart;
	std::vector<const char*>* guidingSymbols;
	ParsingRule(const char* leftPart, std::vector<const char*>* rightPart);
	~ParsingRule();
};

//class ParsingGraph
//{
//private:
//	std::vector<ParsingRule*> rules;
//public:
//	ParsingGraph();
//	void add(ParsingRule* rule);
//	ParsingRule** get(const char* leftPart);
//	ParsingRule* getRoot();
//};