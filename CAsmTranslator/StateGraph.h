#pragma once
#include <vector>
#include "Translator.h"
#include "Token.h"

class StateNode;

class Path
{
public:
	std::regex* regex;
	StateNode* destination;
	Path(StateNode* destination, std::regex* regex);
};

class StateNode
{
public:
	bool (*getResult)(const char*, std::vector<Token*>*);
	std::vector<Path*> paths;
	StateNode(bool (*getResult)(const char*, std::vector<Token*>*));
};

class StateGraph
{
public:
	std::vector<StateNode*> nodes;
	StateNode* curNode;
	StateGraph();
};