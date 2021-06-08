#pragma once
#include <vector>
#include "Token.h"

class ExpressionTree
{
public:
	Token* token;
	ExpressionTree* left;
	ExpressionTree* right;
	ExpressionTree(Token* token);
	~ExpressionTree();
	std::vector<Token*>* getInfix();
	std::vector<Token*>* getPrefix();
	std::vector<Token*>* getPostfix();
};