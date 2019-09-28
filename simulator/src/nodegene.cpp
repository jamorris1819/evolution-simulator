#define euler 2.71828182845904523536028747135266249
#include "nodegene.h"
#include "glm\glm.hpp"

NodeGene::NodeGene(NodeType type)
{
	nodeType = type;
	tempValue = 0;
	useTemp = false;
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
	useTemp = true;
}

bool NodeGene::isSet()
{
	return useTemp;
}

void NodeGene::flush()
{
	tempValue = 0;
	useTemp = false;
}

ActivationFunction NodeGene::getActivationFunction()
{
	return activationFunction;
}

void NodeGene::setActivationFunction(ActivationFunction activationFunction)
{
	this->activationFunction = activationFunction;
}