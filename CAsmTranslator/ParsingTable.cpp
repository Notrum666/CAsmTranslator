#include "ParsingTable.h"

ParsingTable_Record::ParsingTable_Record(Token* terminals, int jump, bool accept, bool stack, bool ret, bool error)
{
	this->terminals = terminals;
	this->jump = jump;
	this->accept = accept;
	this->stack = stack;
	this->ret = ret;
	this->error = error;
}

ParsingTable::ParsingTable()
{
	records = new std::vector<ParsingTable_Record*>();
}

ParsingTable::ParsingTable(std::vector<ParsingTable_Record*>* records)
{
	this->records = records;
}

void ParsingTable::add(ParsingTable_Record* record)
{
	records->push_back(record);
}

ParsingTable_Record* ParsingTable::get(int id)
{
	return (*records)[id];
}

//void checkForNonExistentRules(std::vector<ParsingRule*>* graph)
//{
//	for (auto rule : *graph)
//		for (auto rightPartLine : *(rule->rightPart))
//			if (rightPartLine[0] >= 'A' && rightPartLine[0] <= 'Z')
//			{
//				bool ruleFound = false;
//				for (auto checkRule : *graph)
//					if (std::strcmp(checkRule->leftPart, rightPartLine) == 0)
//					{
//						ruleFound = true;
//						break;
//					}
//				if (!ruleFound)
//				{
//					const char errorBase[] = "Error: rule was not found: ";
//					char* error = (char*)std::calloc(sizeof(errorBase) + strlen(rightPartLine), 1);
//					strcpy(error, rightPartLine);
//					throw error;
//				}
//			}
//}
//
//std::vector<const char*>* getGuidingSymbolsFor(ParsingRule* rule, std::vector<ParsingRule*>* graph)
//{
//	std::vector<ParsingRule*>::iterator iter = std::find(graph->begin(), graph->end(), rule);
//	if (iter == graph->end())
//		return nullptr;
//
//	std::vector<const char*>* symbols = new std::vector<const char*>();
//
//	if (rule->rightPart->size() == 0)
//	{
//		symbols->push_back("{Empty}");
//		return symbols;
//	}
//	const char* rightPart = (*(rule->rightPart))[0];
//	if (rightPart[0] < 'A' || rightPart[0] > 'Z')
//		symbols->push_back(rightPart);
//	else
//	{
//		
//		std::vector<const char*>* subSymbols = getGuidingSymbolsFor
//	}
//}
//
//void generateGuidingSymbols(std::vector<ParsingRule*>* graph)
//{
//	int rulesCount = graph->size();
//	for (int i = 0; i < rulesCount; i++)
//	{
//		std::vector<ParsingRule*>* copy = new std::vector<ParsingRule*>(*graph);
//		(*graph)[i]->guidingSymbols = getGuidingSymbolsFor((*copy)[i], copy);
//		//(*graph)[i]->guidingSymbols = new std::vector<const char*>(*(*copy)[i]->guidingSymbols);
//		delete copy;
//	}
//}
//
////void parseRule(std::vector<ParsingRule*> graph, std::vector<ParsingRule*> rulesLeft, ParsingRule* curRule, std::vector<ParsingTable_Record*> table)
////{
////	int startIndex = -1;
////	//std::vector<ParsingRule*> curRules = std::vector<ParsingRule*>();
////	//int graphSize = rulesLeft.size();
////	//for (int i = 0; i < graphSize; i++)
////	//	if (std::strcmp(rulesLeft[i]->leftPart, ruleName) == 0)
////	//	{
////	//		if (startIndex == -1)
////	//			startIndex = i;
////	//		curRules.push_back(rulesLeft[i]);
////	//		rulesLeft.erase(rulesLeft.begin() + i);
////	//		i--;
////	//		graphSize--;
////	//	}
////
////	for (auto rightPart : curRule->rightParts)
////	{
////		int rightPartSize = rightPart.size();
////		if (rightPart[0][0] < 'A' || rightPart[0][0] > 'Z')
////		{
////
////		}
////		for (int i = 0; i < rightPartSize; i++)
////		{
////
////		}
////	}
////}
//
//ParsingTable* ParsingTable::parse(std::vector<ParsingRule*>* graph)
//{
//	std::vector<ParsingTable_Record*>* table = new std::vector<ParsingTable_Record*>();
//	checkForNonExistentRules(graph);
//	generateGuidingSymbols(graph);
//	//parseRule(graph, rulesLeft, graph[0], table);
//	return new ParsingTable(table);
//}