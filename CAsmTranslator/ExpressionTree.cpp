#include "ExpressionTree.h"

ExpressionTree::ExpressionTree(Token* token)
{
	this->token = token;
	left = nullptr;
	right = nullptr;
}