#include "connectiongene.h"
#include "innovationmanager.h"

ConnectionGene::ConnectionGene()
{
	inputNode = 0;
	outputNode = 0;
	this->enabled = true;
	this->weight = 1.0;
	this->innovation = 0;
}

ConnectionGene::ConnectionGene(int input, int output, bool enabled, double weight)
{
	inputNode = input;
	outputNode = output;
	this->enabled = enabled;
	this->weight = weight;
	this->innovation = InnovationManager::getInnovationNumber(inputNode, outputNode);
}

int ConnectionGene::getInputNode()
{
	return inputNode;
}

int ConnectionGene::getOutputNode()
{
	return outputNode;
}

double ConnectionGene::getWeight()
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

void ConnectionGene::setWeight(double weight)
{
	this->weight = weight;
}