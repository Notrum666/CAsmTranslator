#pragma once
#include <vector>
#include "Token.h"

class ParsingTree
{
public:
	int state;
	Token* token;
	std::vector<ParsingTree*>* leaves;
	ParsingTree* parent;
	ParsingTree(int state, Token* token, ParsingTree* parent);
	void add(ParsingTree* leaf);
};

