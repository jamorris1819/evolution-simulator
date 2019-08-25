#define euler 2.71828182845904523536028747135266249
#include "nodegene.h"
#include "glm\glm.hpp"

NodeGene::NodeGene(NodeType type)
{
	nodeType = type;
	tempValue = 0;
}

NodeGene::~NodeGene()
{

}

NodeType NodeGene::getType()
{
	return nodeType;
}

double NodeGene::getValue()
{
	return tempValue;
}

void NodeGene::setValue(double value)
{
	tempValue = value;
}