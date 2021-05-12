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
};