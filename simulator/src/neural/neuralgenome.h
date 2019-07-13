#pragma once
#include <map>
#include "nodegene.h"
#include "connectiongene.h"

class NeuralGenome {
public:
	NeuralGenome(int inputs, int outputs);
	//~NeuralGenome();
	float* evaluate(float* inputs);
private:
	int inputCount;
	int outputCount;
	std::map<int, NodeGene> nodes;
	std::map<int, ConnectionGene> connections;
	float recurseNetwork(int node, float *inputs);
};