#include "ParsingRule.h"

ParsingRule::ParsingRule(const char* leftPart, std::vector<const char*>* rightPart)
{
	this->leftPart = leftPart;
	this->rightPart = rightPart;
	guidingSymbols = new std::vector<const char*>();
}

ParsingRule::~ParsingRule()
{
	delete leftPart;
	for (auto line : *rightPart)
		delete line;
	delete rightPart;
	delete guidingSymbols;
}

//ParsingGraph::ParsingGraph()
//{
//	rules = std::vector<ParsingRule*>();
//}
//
//void ParsingGraph::add(ParsingRule* rule)
//{
//	rules.push_back(rule);
//}
//
//ParsingRule** ParsingGraph::get(const char* leftPart)
//{
//	ParsingRule** curRules = (ParsingRule**)std::calloc(rules.size(), sizeof(void*));
//	int count = 0;
//
//	for (auto rule : rules)
//		if (std::strcmp(rule->leftPart, leftPart) == 0)
//			curRules[count++] = rule;
//
//	curRules = (ParsingRule**)std::realloc(curRules, count * sizeof(void*));
//	return curRules;
//}
//
//ParsingRule* ParsingGraph::getRoot()
//{
//	return rules[0];
//}