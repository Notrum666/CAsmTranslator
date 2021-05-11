#include "ParsingTree.h"

ParsingTree::ParsingTree(int state, Token* token, ParsingTree* parent)
{
	this->state = state;
	this->token = token;
	this->parent = parent;
	leaves = new std::vector<ParsingTree*>();
}

void ParsingTree::add(ParsingTree* leaf)
{
	this->leaves->push_back(leaf);
}