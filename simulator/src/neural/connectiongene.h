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
	float evaluate(float input);
	void setEnabled(bool enabled);
private:
	int inputNode;
	int outputNode;
	bool enabled;
	float weight;
	int innovation;
};