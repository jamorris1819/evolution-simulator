#pragma once
#include <map>
#include "nodegene.h"
#include "connectiongene.h"

class NeuralGenome {
public:
	NeuralGenome(int inputs, int outputs);
	//~NeuralGenome();
	float* evaluate(float* inputs);
	int inputCount;
	int outputCount;
	int getNodeCount();
	std::map<int, NodeGene> getNodes();
	std::map<int, ConnectionGene> getConnections();
private:
	std::map<int, NodeGene> nodes;
	std::map<int, ConnectionGene> connections;
	float recurseNetwork(int node, float *inputs);
};