#pragma once
#include <map>
#include "nodegene.h"
#include "connectiongene.h"

class NeuralGenome {
public:
	NeuralGenome(int inputs, int outputs);
	NeuralGenome(std::map<int, NodeGene> nodes, std::map<int, ConnectionGene> connections);
	//~NeuralGenome();
	double* evaluate(double* inputs);
	static NeuralGenome* cross(NeuralGenome* genome1, NeuralGenome* genome2);
	int findLargestInnovation();
	int innovationPresent(int innovationNumber);
	int inputCount;
	int outputCount;
	int getNodeCount();
	std::map<int, NodeGene> getNodes();
	std::map<int, ConnectionGene> getConnections();
	void mutateAddConnection();
	void mutateAddNode();
	void mutateShiftWeight();
	void mutateRandomWeight();
	void mutateToggleConnection();
private:
	std::map<int, NodeGene> nodes;
	std::map<int, ConnectionGene> connections;
	double activateFunction(int node, double value);
	void setNodeValue(int node, double value);
	double recurseNetwork(int node, double *inputs);
	bool tryAddConnection(int& fromNode, int& toNode);
	bool getRandomConnection(ConnectionGene** connectionGene);
	static int innovationNumber;
	double randomWeight();
};

