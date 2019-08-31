#pragma once
#include "nodegene.h"

class ConnectionGene {
public:
	ConnectionGene();
	ConnectionGene(int input, int output, bool enabled, double weight);
	int getInputNode();
	int getOutputNode();
	double getWeight();
	bool getEnabled();
	int getInnovation();
	void setWeight(double weight);
	void setEnabled(bool enabled);
private:
	int inputNode;
	int outputNode;
	bool enabled;
	double weight;
	int innovation;
};