#include "StateGraph.h"
#include "Error.h"

Path::Path(StateNode* destination, std::regex* regex)
{
	this->destination = destination;
	this->regex = regex;
}

StateNode::StateNode(Error* (*getResult)(const char*, std::vector<Token*>*))
{
	this->paths = std::vector<Path*>();
	this->getResult = getResult;
}

Error* getResult_D(const char* buffer, std::vector<Token*>* tokens)
{
	int id;
	while (*buffer != '\0')
	{
		if ((id = Translator::delimeters->getIdBySymbol(*buffer)) != -1)
		{
			if (!Translator::delimeters->get(id)->skip)
				tokens->push_back(new Token(1, id));
		}
		else return new Error(nullptr, 0, 0, "undefined delimeter");
		buffer++;
	}
	return nullptr;
}

Error* getResult_L(const char* buffer, std::vector<Token*>* tokens)
{
	int id;
	if ((id = Translator::keywords->getIdByKeyword(buffer)) != -1)
	{
		tokens->push_back(new Token(0, id));
		return nullptr;
	}
	if ((id = Translator::identifiers->getIdByName(buffer)) != -1)
	{
		tokens->push_back(new Token(2, id));
		return nullptr;
	}
	int len = (std::strlen(buffer) + 1);
	char* name = (char*)std::malloc(len * sizeof(char));
	strcpy_s(name, len, buffer);
	tokens->push_back(new Token(2, Translator::identifiers->add(new Record_Identifiers(name, nullptr, Type::type_int))));
	return nullptr;
}

Error* getResult_O(const char* buffer, std::vector<Token*>* tokens)
{
	int id;
	if ((id = Translator::keywords->getIdByKeyword(buffer)) != -1)
	{
		tokens->push_back(new Token(0, id));
		return nullptr;
	}
	return new Error(nullptr, 0, 0, "undefined keyword");
}

Error* getResult_N(const char* buffer, std::vector<Token*>* tokens)
{
	int id;
	int* value = (int*)std::malloc(sizeof(int));
	*value = atoi(buffer);
	if ((id = Translator::constants->getIdByValue(value)) == -1)
		id = Translator::constants->add(new Record_Constants(value, Type::type_int));
	tokens->push_back(new Token(3, id));
	return nullptr;
}

Error* getResult_DoNothing(const char* buffer, std::vector<Token*>* tokens)
{
	return nullptr;
}

StateGraph::StateGraph()
{
	nodes = std::vector<StateNode*>();

	StateNode* D = new StateNode(getResult_D);
	StateNode* L = new StateNode(getResult_L);
	StateNode* O = new StateNode(getResult_O);
	StateNode* N = new StateNode(getResult_N);
	StateNode* SL = new StateNode(getResult_DoNothing);
	StateNode* C = new StateNode(getResult_DoNothing);
	StateNode* CE = new StateNode(getResult_DoNothing);
	StateNode* MLC = new StateNode(getResult_DoNothing);
	StateNode* MLCS = new StateNode(getResult_DoNothing);
	StateNode* MLCE = new StateNode(getResult_DoNothing);

	std::regex* regex_delimeters = new std::regex("[ \n\t;(){}]");
	std::regex* regex_letters = new std::regex("[a-zA-Z_]");
	std::regex* regex_operators = new std::regex("[\\+\\-=!<>]");
	std::regex* regex_numbers = new std::regex("[0-9]");
	std::regex* regex_slash = new std::regex("[/]");

	D->paths.push_back(new Path(D, regex_delimeters));
	D->paths.push_back(new Path(L, regex_letters));
	D->paths.push_back(new Path(O, regex_operators));
	D->paths.push_back(new Path(N, regex_numbers));
	D->paths.push_back(new Path(SL, regex_slash));

	L->paths.push_back(new Path(D, regex_delimeters));
	L->paths.push_back(new Path(L, regex_letters));
	L->paths.push_back(new Path(O, regex_operators));
	L->paths.push_back(new Path(SL, regex_slash));

	O->paths.push_back(new Path(D, regex_delimeters));
	O->paths.push_back(new Path(L, regex_letters));
	O->paths.push_back(new Path(O, regex_operators));
	O->paths.push_back(new Path(N, regex_numbers));
	O->paths.push_back(new Path(SL, regex_slash));

	N->paths.push_back(new Path(D, regex_delimeters));
	N->paths.push_back(new Path(O, regex_operators));
	N->paths.push_back(new Path(N, regex_numbers));
	N->paths.push_back(new Path(SL, regex_slash));

	SL->paths.push_back(new Path(C, regex_slash));
	SL->paths.push_back(new Path(MLC, new std::regex("[\\*]")));

	C->paths.push_back(new Path(C, new std::regex("[^\n]")));
	C->paths.push_back(new Path(CE, new std::regex("[\n]")));

	CE->paths.push_back(new Path(D, regex_delimeters));
	CE->paths.push_back(new Path(L, regex_letters));
	CE->paths.push_back(new Path(O, regex_operators));
	CE->paths.push_back(new Path(N, regex_numbers));
	CE->paths.push_back(new Path(SL, regex_slash));

	MLC->paths.push_back(new Path(MLC, new std::regex("[^\\*]")));
	MLC->paths.push_back(new Path(MLCS, new std::regex("[\\*]")));

	MLCS->paths.push_back(new Path(MLC, new std::regex("[^/]")));
	MLCS->paths.push_back(new Path(MLCE, regex_slash));

	MLCE->paths.push_back(new Path(D, regex_delimeters));
	MLCE->paths.push_back(new Path(L, regex_letters));
	MLCE->paths.push_back(new Path(O, regex_operators));
	MLCE->paths.push_back(new Path(N, regex_numbers));
	MLCE->paths.push_back(new Path(SL, regex_slash));

	curNode = D;
}