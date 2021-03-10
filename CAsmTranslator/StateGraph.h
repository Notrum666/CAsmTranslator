#pragma once
#include <vector>
#include "Translator.h"

class Path
{
public:
	const char* alphabet;
	StateNode* destination;
	Path(const char* alphabet);
};

class StateNode
{
public:
	Token** getResult;
	std::vector<Path*> paths;
	StateNode(Token** getResult);
};

class StateGraph
{
public:
	std::vector<StateNode*> nodes;
	StateNode* curNode;
	StateGraph();
};