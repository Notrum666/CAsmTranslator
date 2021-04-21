#pragma once
#include <vector>
#include "Translator.h"
#include "Token.h"
#include "Error.h"

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
	Error* (*getResult)(const char*, std::vector<Token*>*);
	std::vector<Path*> paths;
	StateNode(Error* (*getResult)(const char*, std::vector<Token*>*));
};

class StateGraph
{
public:
	std::vector<StateNode*> nodes;
	StateNode* curNode;
	StateGraph();
};