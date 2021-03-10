#include "StateGraph.h"

Path::Path(const char* alphabet)
{
	this->alphabet = alphabet;
}

StateNode::StateNode(Token** getResult)
{
	paths = std::vector<Path*>();
}

Token* getResult_d(const char* buffer)
{
	
}

StateGraph::StateGraph()
{
	nodes = std::vector<StateNode*>();

	StateNode* D = new StateNode()
}