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
	std::vector<Token*>* getInfix();
	std::vector<Token*>* getPrefix();
	std::vector<Token*>* getPostfix();
};