#pragma once
#include <map>
#include "nodegene.h"
#include "connectiongene.h"

class NeuralGenome {
public:
	NeuralGenome(int inputs, int outputs);
	//~NeuralGenome();
	double* evaluate(double* inputs);
	int inputCount;
	int outputCount;
	int getNodeCount();
	static int getNewInnovationNumber()
	{
		return ++innovationNumber;
	}
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

