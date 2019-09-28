#pragma once
#include <map>
#include "nodegene.h"
#include "connectiongene.h"
#include <vector>

class NeuralGenome {
public:
	NeuralGenome(int inputs, int outputs);
	NeuralGenome(std::vector<std::pair<int, NodeGene>> nodes, std::vector<std::pair<int, ConnectionGene>> connections);
	//~NeuralGenome();
	double* evaluate(double* inputs);
	static NeuralGenome* cross(NeuralGenome* genome1, NeuralGenome* genome2);
	int findLargestInnovation();
	int innovationPresent(int innovationNumber);
	int inputCount;
	int outputCount;
	int getNodeCount();
	std::vector<std::pair<int, NodeGene>> getNodes();
	std::vector<std::pair<int, ConnectionGene>> getConnections();
	void mutateAddConnection();
	void mutateAddNode();
	void mutateShiftWeight();
	void mutateRandomWeight();
	void mutateToggleConnection();
private:
	std::vector<std::pair<int, NodeGene>> nodes;
	std::vector<std::pair<int, ConnectionGene>> connections;
	NodeGene& getNode(int index);

	double activateFunction(int node, double value);
	void setNodeValue(int node, double value);
	double recurseNetwork(int node, double *inputs);

	// Helper methods for mutation
	bool tryAddConnection(int& input, int& output);
	void generateRandomConnection(int& input, int& output);
	bool connectionExists(int input, int output);
	bool getRandomConnection(ConnectionGene** connectionGene);

	static int innovationNumber;
	double randomWeight();
};

