#include "ExpressionTree.h"

ExpressionTree::ExpressionTree(Token* token)
{
	this->token = token;
	left = nullptr;
	right = nullptr;
}

std::vector<Token*>* ExpressionTree::getInfix()
{
	std::vector<Token*>* data = new std::vector<Token*>();
	if (left != nullptr)
	{
		std::vector<Token*>* l = left->getInfix();
		data->insert(data->end(), l->begin(), l->end());
		delete l;
	}
	data->push_back(token);
	if (right != nullptr)
	{
		std::vector<Token*>* r = right->getInfix();
		data->insert(data->end(), r->begin(), r->end());
		delete r;
	}
	return data;
}

std::vector<Token*>* ExpressionTree::getPostfix()
{
	std::vector<Token*>* data = new std::vector<Token*>();
	if (left != nullptr)
	{
		std::vector<Token*>* l = left->getPostfix();
		data->insert(data->end(), l->begin(), l->end());
		delete l;
	}
	if (right != nullptr)
	{
		std::vector<Token*>* r = right->getPostfix();
		data->insert(data->end(), r->begin(), r->end());
		delete r;
	}
	data->push_back(token);
	return data;
}

std::vector<Token*>* ExpressionTree::getPrefix()
{
	std::vector<Token*>* data = new std::vector<Token*>();
	data->push_back(token);
	if (left != nullptr)
	{
		std::vector<Token*>* l = left->getPrefix();
		data->insert(data->end(), l->begin(), l->end());
		delete l;
	}
	if (right != nullptr)
	{
		std::vector<Token*>* r = right->getPrefix();
		data->insert(data->end(), r->begin(), r->end());
		delete r;
	}
	return data;
}