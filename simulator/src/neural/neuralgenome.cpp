#include "neuralgenome.h"
#include <vector>
#include "../util/Function.h"

int NeuralGenome::innovationNumber = 0;


NeuralGenome::NeuralGenome(int inputs, int outputs)
{
	// Create input nodes.
	for (int i = 0; i < inputs; i++) {
		NodeGene nodeGene(NodeType::INPUT);
		nodeGene.setActivationFunction(ActivationFunction::NONE);
		nodes.insert(std::make_pair(nodes.size(), nodeGene));
	}

	// Create output nodes.
	for (int i = 0; i < outputs; i++) {
		NodeGene nodeGene(NodeType::OUTPUT);
		nodeGene.setActivationFunction(ActivationFunction::SIGMOID);
		nodes.insert(std::make_pair(nodes.size(), nodeGene));
	}

	inputCount = inputs;
	outputCount = outputs;	
}

NeuralGenome::NeuralGenome(std::map<int, NodeGene> nodes, std::map<int, ConnectionGene> connections)
{
	this->nodes.insert(nodes.begin(), nodes.end());
	this->connections.insert(connections.begin(), connections.end());

	inputCount = 0;
	outputCount = 0;

	for (int i = 0; i < nodes.size(); i++) {
		if (nodes.at(i).getType() == NodeType::INPUT) inputCount++;
		if (nodes.at(i).getType() == NodeType::OUTPUT) outputCount++;
	}
}

double* NeuralGenome::evaluate(double* inputs)
{
	double* outputs = new double[outputCount];

	for (int i = 0; i < outputCount; i++) {
		outputs[i] = Function::sigmoid(recurseNetwork(inputCount + i, inputs));
	}

	return outputs;
}

// Find the value of the node by recursing down the network.
double NeuralGenome::recurseNetwork(int node, double *inputs)
{
	double toReturn = 0.0;

	std::map<int, ConnectionGene>::iterator it;
	std::vector<ConnectionGene> genes;

	// Gather a list of connections originating or ending at this node.
	for (it = connections.begin(); it != connections.end(); it++)
	{
		ConnectionGene connGene = it->second;
		if (connGene.getOutputNode() == node)
			genes.push_back(connGene);
	}

	// Iterate through all relevant connections to determine value of node.
	for (int i = 0; i < genes.size(); i++) {
		ConnectionGene connGene = genes[i];
		int attachedNode = connGene.getInputNode();

		// If disabled then skip.
		if (!connGene.getEnabled()) continue;

		// If less than input count then it's an input node.
		if (attachedNode < inputCount) {
			toReturn += inputs[attachedNode] * connGene.getWeight();
			setNodeValue(attachedNode, inputs[attachedNode]);
			continue;
		}
		
		// If it's a hidden node then we must recurse further.
		double recurseValue = recurseNetwork(attachedNode, inputs);
		double val = activateFunction(connGene.getInputNode(), recurseValue * connGene.getWeight());

		toReturn += val;
	}

	float value = toReturn;
	setNodeValue(node, value);
	return value;
}

// Performs the activation function required by that node.
double NeuralGenome::activateFunction(int node, double value)
{
	ActivationFunction func = nodes.at(node).getActivationFunction();

	switch (func) {
	case ActivationFunction::SIGMOID:
		return Function::sigmoid(value);

	case ActivationFunction::RELU:
		return Function::relu(value);
	}

	return value;
}

// Sets the node's value for use in rendering.
void NeuralGenome::setNodeValue(int node, double value)
{
	nodes.at(node).setValue(value);
}

int NeuralGenome::getNodeCount()
{
	return nodes.size();
}

std::map<int, ConnectionGene> NeuralGenome::getConnections()
{
	return connections;
}

std::map<int, NodeGene> NeuralGenome::getNodes()
{
	return nodes;
}

/*
	C R O S S I N G
*/

// Find the largest innovation number present in the genome.
int NeuralGenome::findLargestInnovation()
{
	int genomeSize = connections.size();
	int largestInnovation = -1;

	for (int i = 0; i < genomeSize; i++) {
		if (connections.at(i).getInnovation() > largestInnovation) largestInnovation = connections.at(i).getInnovation();
	}

	return largestInnovation;
}

// Checks to see if the innovation is present in the genome.
int NeuralGenome::innovationPresent(int innovationNumber)
{
	for (int j = 0; j < connections.size(); j++) {
		if (connections.at(j).getInnovation() == innovationNumber) {
			return j;
		}
	}

	return -1;
}

// Crosses the 2 genomes to create a child.
NeuralGenome* NeuralGenome::cross(NeuralGenome* genome1, NeuralGenome* genome2)
{
 	std::map<int, NodeGene> nodes;
	std::map<int, ConnectionGene> connections;

	int largestInnovation1 = genome1->findLargestInnovation();
	int largestInnovation2 = genome2->findLargestInnovation();

	int largestInnovation = glm::max(largestInnovation1, largestInnovation2);

	// Iterate through the connection genes and cross.
	for (int i = 0; i <= largestInnovation; i++) {
		// Check if the a gene with this innovation number exists in both genomes.
		int locationInGenome1 = genome1->innovationPresent(i);
		int locationInGenome2 = genome2->innovationPresent(i);

		// If this innovation is present in both, choose one at random.
		if (locationInGenome1 >= 0 && locationInGenome2 >= 0) {
			connections.insert(std::make_pair(connections.size(),
				rand() % 2 == 0 ? genome1->connections.at(locationInGenome1) : genome2->connections.at(locationInGenome2)
			));
		}
		// If it isn't in both, take the copy from the genome where it does exist.
		else if (locationInGenome1 >= 0) {
			connections.insert(std::make_pair(connections.size(), genome1->connections.at(locationInGenome1)));
		}
		else if (locationInGenome2 >= 0) {
			connections.insert(std::make_pair(connections.size(), genome2->connections.at(locationInGenome2)));
		}
	}

	// Create the node genes. // todo check this works
	bool genome1MoreNodes = genome1->nodes.size() > genome2->nodes.size();

	if (genome1MoreNodes)
		nodes.insert(genome1->nodes.begin(), genome1->nodes.end());
	else
		nodes.insert(genome2->nodes.begin(), genome2->nodes.end());

	return new NeuralGenome(nodes, connections);
}

/*
		M U T A T I O N S
*/

// Attempts to find 2 nodes to create a connection between.
bool NeuralGenome::tryAddConnection(int& fromNode, int& toNode)
{
	bool hiddenNodesExist = getNodeCount() > inputCount + outputCount;	// If there are hidden nodes in this neural network.
	bool useHiddenNode = hiddenNodesExist && rand() % 2 == 0;			// If we want to involve a hidden node in this connection.

	if (useHiddenNode) {
		bool startOnHidden = rand() % 2 == 0;
		int hiddenNodeCount = getNodeCount() - inputCount - outputCount;
		int hiddenNodeToUse = inputCount + outputCount + (rand() % hiddenNodeCount);

		if (startOnHidden) {
			fromNode = hiddenNodeToUse;						// hidden node
			toNode = inputCount + (rand() % outputCount);	// an output node
		}
		else {
			toNode = hiddenNodeToUse;
			fromNode = rand() % 2 == 0										// randomly choose:
				? rand() % inputCount										// input node
				: inputCount + outputCount + (rand() % hiddenNodeCount);	// hidden node
		}
	}
	else {
		fromNode = rand() % inputCount;					// input node
		toNode = inputCount + (rand() % outputCount);	// output node
	}

	// A connection can't go from itself to itself.
	if (fromNode == toNode) return false;

	// Check if these nodes already have a connection.
	for (int j = 0; j < connections.size(); j++) {
		ConnectionGene connGene = connections[j];
		if ((connGene.getInputNode() == fromNode && connGene.getOutputNode() == toNode)
			|| (connGene.getInputNode() == toNode && connGene.getOutputNode() == fromNode)) {
			return false;
		}
	}

	return true;
}

// Mutates the genome by creating a new connection between 2 random nodes.
void NeuralGenome::mutateAddConnection()
{
	int fromNode = 0;
	int toNode = 0;
	bool canMutate = false;

	for (int i = 0; i < 5; i++) {
		canMutate = canMutate || tryAddConnection(fromNode, toNode);
		if (canMutate) break;
	}

	if (!canMutate) return;

	double weight = randomWeight();;

	// Create the connection
	ConnectionGene gene(fromNode, toNode, true, weight);
	connections.insert(std::make_pair(connections.size(), gene));
}

// Mutates the genome by creating a new node in the middle of an existing connection.
void NeuralGenome::mutateAddNode()
{
	ConnectionGene* existingConnection = nullptr;
	if (!getRandomConnection(&existingConnection) || !existingConnection->getEnabled()) return;

	// Get its input + output node.
	int fromNode = existingConnection->getInputNode();
	int toNode = existingConnection->getOutputNode();

	// Disable it as we're replacing it.
	existingConnection->setEnabled(false);

	// Add a new node in between.
	NodeGene newNode(NodeType::HIDDEN);
	newNode.setActivationFunction(ActivationFunction::RELU);
	nodes.insert(std::make_pair(nodes.size(), newNode));
	int newNodeIndex = getNodeCount() - 1;

	// Now create 2 connections with the new node in the middle.
	ConnectionGene connection1(fromNode, newNodeIndex, true, 1.0);		// weight of 1 to preserve original
	connections.insert(std::make_pair(connections.size(), connection1));

	double weight = existingConnection->getWeight();
	ConnectionGene connection2(newNodeIndex, toNode, true, weight);
	connections.insert(std::make_pair(connections.size(), connection2));
}

// Mutates the genome by randomly shifting a weight up or down.
void NeuralGenome::mutateShiftWeight()
{
	ConnectionGene* existingConnection = nullptr;
	if (!getRandomConnection(&existingConnection)) return;

	bool shiftUp = rand() % 2 == 0;
	double weight = existingConnection->getWeight();
	weight += shiftUp ? 0.1 : -0.1;
	weight = glm::clamp(weight, -1.0, 1.0);

	existingConnection->setWeight(weight);
}

// Mutates the genome by creating setting a random connection's weight to a random number.
void NeuralGenome::mutateRandomWeight()
{
	ConnectionGene* existingConnection = nullptr;
	if (!getRandomConnection(&existingConnection)) return;
	existingConnection->setWeight(randomWeight());
}

// Mutates the genome by toggling (enabled/disabled) a connection.
void NeuralGenome::mutateToggleConnection()
{
	ConnectionGene* existingConnection = nullptr;
	if (!getRandomConnection(&existingConnection)) return;
	existingConnection->setEnabled(!existingConnection->getEnabled());
}

// Gets a random connection from the genome.
bool NeuralGenome::getRandomConnection(ConnectionGene** connectionGene)
{
	// Get a random connection gene.
	int connectionCount = connections.size();
	if (connectionCount == 0) return false;

	int connectionToSplit = rand() % connectionCount;
	*connectionGene = &connections[connectionToSplit];

	return true;
}

// Generates a random weight between -1.0 and 1.0
double NeuralGenome::randomWeight()
{
	return (((double)rand() / (RAND_MAX)) * 2.0) - 1.0;
}