#include "connectiongene.h"

ConnectionGene::ConnectionGene(int input, int output, bool enabled, float weight, int innovation)
{
	inputNode = input;
	outputNode = output;
	this->enabled = enabled;
	this->weight = weight;
	this->innovation = innovation;
}

int ConnectionGene::getInputNode()
{
	return inputNode;
}

int ConnectionGene::getOutputNode()
{
	return outputNode;
}

float ConnectionGene::getWeight()
{
	return weight;
}

bool ConnectionGene::getEnabled()
{
	return enabled;
}

int ConnectionGene::getInnovation()
{
	return innovation;
}

void ConnectionGene::setEnabled(bool enabled)
{
	this->enabled = enabled;
}