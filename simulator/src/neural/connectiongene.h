#pragma once
#include "nodegene.h"

class ConnectionGene {
public:
	ConnectionGene(int input, int output, bool enabled, float weight, int innovation);
	int getInputNode();
	int getOutputNode();
	float getWeight();
	bool getEnabled();
	int getInnovation();
private:
	int inputNode;
	int outputNode;
	bool enabled;
	float weight;
	int innovation;
};