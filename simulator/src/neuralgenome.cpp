#include "neuralgenome.h"
#include <vector>
#include "Function.h"

int NeuralGenome::innovationNumber = 0;


NeuralGenome::NeuralGenome(int inputs, int outputs)
{
	// Create input nodes.
	for (int i = 0; i < inputs; i++) {
		NodeGene nodeGene(NodeType::INPUT);
		nodeGene.setActivationFunction(ActivationFunction::NONE);
		nodes.push_back(std::make_pair(nodes.size(), nodeGene));
	}

	// Create output nodes.
	for (int i = 0; i < outputs; i++) {
		NodeGene nodeGene(NodeType::OUTPUT);
		nodeGene.setActivationFunction(ActivationFunction::NONE);
		nodes.push_back(std::make_pair(nodes.size(), nodeGene));
	}

	inputCount = inputs;
	outputCount = outputs;	
}

NeuralGenome::NeuralGenome(std::vector<std::pair<int, NodeGene>> nodes, std::vector<std::pair<int, ConnectionGene>> connections)
{
	// Copy the genes over.
	this->nodes = nodes;
	this->connections = connections;

	inputCount = 0;
	outputCount = 0;

	for (int i = 0; i < nodes.size(); i++) {
		if (nodes[i].second.getType() == NodeType::INPUT) inputCount++;
		if (nodes[i].second.getType() == NodeType::OUTPUT) outputCount++;
	}
}

// Evaluates the network and performs all calculations.
double* NeuralGenome::evaluate(double* inputs)
{
	double* outputs = new double[outputCount];

	for (int i = 0; i < outputCount; i++) {
		outputs[i] = Function::sigmoid(recurseNetwork(inputCount + i, inputs));
	}

	// Flush the temporary node values.
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i].second.flush();
	}

	return outputs;
}

// Find the value of the node by recursing down the network.
double NeuralGenome::recurseNetwork(int node, double *inputs)
{
	// Check if this node has already been evaluated.
	if (getNode(node).isSet()) {
		return getNode(node).getValue();
	}

	double toReturn = 0.0;
	std::vector<std::pair<int, ConnectionGene>> genes;

	// Gather a list of connections originating or ending at this node.
	for (int i = 0; i < connections.size(); i++)
	{
		ConnectionGene connGene = connections[i].second;
		if (connGene.getOutputNode() == node) {
			bool containedGene = false;
			for (int j = 0; j < genes.size(); j++) {
				if (genes[j].first == node) {
					containedGene = true;
					break;
				}
			}
			if(!containedGene) genes.push_back(connections[i]);
		}
	}

	// Iterate through all relevant connections to determine value of node.
	for (int i = 0; i < genes.size(); i++) {
		ConnectionGene connGene = genes[i].second;
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
	getNode(node).setValue(value);
	return value;
}

NodeGene& NeuralGenome::getNode(int index)
{
	return nodes[index].second;
}

// Performs the activation function required by that node.
double NeuralGenome::activateFunction(int node, double value)
{
	ActivationFunction func = nodes[node].second.getActivationFunction();

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
	nodes[node].second.setValue(value);
}

int NeuralGenome::getNodeCount()
{
	return nodes.size();
}

std::vector<std::pair<int, ConnectionGene>> NeuralGenome::getConnections()
{
	return connections;
}

std::vector<std::pair<int, NodeGene>> NeuralGenome::getNodes()
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
		if (connections[i].second.getInnovation() > largestInnovation) largestInnovation = connections[i].second.getInnovation();
	}

	return largestInnovation;
}

// Checks to see if the innovation is present in the genome.
int NeuralGenome::innovationPresent(int innovationNumber)
{
	for (int j = 0; j < connections.size(); j++) {
		if (connections[j].second.getInnovation() == innovationNumber) {
			return j;
		}
	}

	return -1;
}

// Crosses the 2 genomes to create a child.
NeuralGenome* NeuralGenome::cross(NeuralGenome* genome1, NeuralGenome* genome2)
{
	/*
		TODO: Ensure disjoint genes are taken from the fitter parent.
	*/

	std::vector<std::pair<int, NodeGene>> nodes;
	std::vector<std::pair<int, ConnectionGene>> connections;

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
			connections.push_back(std::make_pair(connections.size(),
				rand() % 2 == 0 ? genome1->connections[locationInGenome1].second : genome2->connections[locationInGenome2].second
			));
		}
		// If it isn't in both, take the copy from the genome where it does exist.
		else if (locationInGenome1 >= 0) {
			connections.push_back(std::make_pair(connections.size(), genome1->connections[locationInGenome1].second));
		}
		else if (locationInGenome2 >= 0) {
			connections.push_back(std::make_pair(connections.size(), genome2->connections[locationInGenome2].second));
		}
	}

	// Create the node genes. // todo check this works
	bool genome1MoreNodes = genome1->nodes.size() > genome2->nodes.size();

	if (genome1MoreNodes)
		nodes = genome1->nodes;
	else
		nodes = genome2->nodes;

	return new NeuralGenome(nodes, connections);
}

/*
		M U T A T I O N S
*/

// Mutates the genome by creating a new connection between 2 random nodes.
void NeuralGenome::mutateAddConnection()
{
	int fromNode = 0;
	int toNode = 0;
	bool canMutate = false;

	// Try and find a connection which can be used.
	for (int i = 0; i < inputCount * outputCount; i++) {
		canMutate = canMutate || tryAddConnection(fromNode, toNode);
		if (canMutate) break;
	}

	if (!canMutate) return;

	double weight = randomWeight();;

	// Create the connection
	ConnectionGene gene(fromNode, toNode, true, weight);
	connections.push_back(std::make_pair(connections.size(), gene));
}

// Mutates the genome by creating a new node in the middle of an existing connection.
void NeuralGenome::mutateAddNode()
{
	ConnectionGene* existingConnection = nullptr;
	if (!getRandomConnection(&existingConnection) || !existingConnection->getEnabled()) return;
	
	// Get node data.
	int fromNode = existingConnection->getInputNode();
	int toNode = existingConnection->getOutputNode();
	double weight = existingConnection->getWeight();

	// Disable it as we're replacing it.
	existingConnection->setEnabled(false);

	// Add a new node in between.
	NodeGene newNode(NodeType::HIDDEN);
	newNode.setActivationFunction(ActivationFunction::RELU);
	nodes.push_back(std::make_pair(nodes.size(), newNode));
	int newNodeIndex = getNodeCount() - 1;

	// Now create 2 connections with the new node in the middle.
	ConnectionGene connection1(fromNode, newNodeIndex, true, 1.0);		// weight of 1 to preserve original
	connections.push_back(std::make_pair(connections.size(), connection1));

	ConnectionGene connection2(newNodeIndex, toNode, true, weight);
	connections.push_back(std::make_pair(connections.size(), connection2));
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

// Finds the average number of nodes between the given node and the input node.
double NeuralGenome::nodeDistanceFromInput(int node)
{
	double toReturn = 0.0;
	std::vector<std::pair<int, ConnectionGene>> genes;

	if (node < inputCount) return 0.0;

	// Gather a list of connections ending at this node.
	for (int i = 0; i < connections.size(); i++)
	{
		ConnectionGene connGene = connections[i].second;
		if (connGene.getEnabled() && connGene.getOutputNode() == node) {
			bool containedGene = false;
			for (int j = 0; j < genes.size(); j++) {
				if (genes[j].first == node) {
					containedGene = true;
					break;
				}
			}
			if (!containedGene) genes.push_back(connections[i]);
		}
	}
	if (genes.size() == 0) return 0.0;

	//return 1.0 + nodeDistanceFromInput(genes[0].second.getInputNode());

	
	int connectionCount = genes.size();
	double sumCount = 0;
	for (int i = 0; i < connectionCount; i++) {
		sumCount += nodeDistanceFromInput(genes[i].second.getInputNode());
	}
	sumCount /= (double)connectionCount;

	return 1 + sumCount;
}

// Finds the average number of nodes between the given node and an output node.
double NeuralGenome::nodeDistanceFromOutput(int node)
{
	double toReturn = 0.0;
	std::vector<std::pair<int, ConnectionGene>> genes;

	if (node > inputCount && node < inputCount + outputCount) return 0.0;

	// Gather a list of connections starting at this node.
	for (int i = 0; i < connections.size(); i++)
	{
		ConnectionGene connGene = connections[i].second;
		if (connGene.getEnabled() && connGene.getInputNode() == node) {
			bool containedGene = false;
			for (int j = 0; j < genes.size(); j++) {
				if (genes[j].first == node) {
					containedGene = true;
					break;
				}
			}
			if (!containedGene) genes.push_back(connections[i]);
		}
	}
	if (genes.size() == 0) return 0.0;

	//return 1.0 + nodeDistanceFromOutput(genes[0].second.getOutputNode());

	
	int connectionCount = genes.size();
	double sumCount = 0;
	for (int i = 0; i < connectionCount; i++) {
		sumCount += nodeDistanceFromInput(genes[i].second.getInputNode());
	}
	sumCount /= (double)connectionCount;

	return 1 + sumCount;
}

int NeuralGenome::nodeMaxDistanceFromInput(int node)
{
	std::vector<std::pair<int, ConnectionGene>> genes;

	if (node < inputCount) return 0.0;

	// Gather a list of connections ending at this node.
	for (int i = 0; i < connections.size(); i++)
	{
		ConnectionGene connGene = connections[i].second;
		if (connGene.getEnabled() && connGene.getOutputNode() == node) {
			bool containedGene = false;
			for (int j = 0; j < genes.size(); j++) {
				if (genes[j].first == node) {
					containedGene = true;
					break;
				}
			}
			if (!containedGene) genes.push_back(connections[i]);
		}
	}
	if (genes.size() == 0) return 0.0;

	int connectionCount = genes.size();
	int largestDistance = 0;
	for (int i = 0; i < connectionCount; i++) {
		int dist = nodeMaxDistanceFromInput(genes[i].second.getInputNode());
		if (dist > largestDistance) largestDistance = dist;
	}

	return 1 + largestDistance;




	return 0;
}

/*
		M U T A T I O N  H E L P E R  M E T H O D S
*/

// Check if a connection exists between the two nodes.
bool NeuralGenome::connectionExists(int input, int output)
{
	for (int j = 0; j < connections.size(); j++) {
		ConnectionGene connGene = connections[j].second;
		if ((connGene.getInputNode() == input && connGene.getOutputNode() == output)
			|| (connGene.getInputNode() == output && connGene.getOutputNode() == input)) {
			return false;
		}
	}

	return true;
}

// Chooses 2 nodes to be used for the new connection.
void NeuralGenome::generateRandomConnection(int& input, int& output)
{
	bool hiddenNodesExist = getNodeCount() > inputCount + outputCount;	// If there are hidden nodes in this neural network.
	bool useHiddenNode = hiddenNodesExist && rand() % 2 == 0;			// If we want to involve a hidden node in this connection.

	// If we're going for an input->output connection.
	if (!useHiddenNode) {
		input = rand() % inputCount;					// an input node
		output = inputCount + (rand() % outputCount);	// an output node
		return;
	}

	bool startOnHidden = rand() % 2 == 0;
	int hiddenNodeCount = getNodeCount() - inputCount - outputCount;
	int hiddenNodeToUse = inputCount + outputCount + (rand() % hiddenNodeCount);

	if (startOnHidden) {
		input = hiddenNodeToUse;						// hidden node
		output = inputCount + (rand() % outputCount);	// an output node
	}
	else {
		output = hiddenNodeToUse;
		input = rand() % 2 == 0										// randomly choose:
			? rand() % inputCount										// input node
			: inputCount + outputCount + (rand() % hiddenNodeCount);	// hidden node
	}
}

// Attempts to find 2 nodes to create a connection between.
bool NeuralGenome::tryAddConnection(int& input, int& output)
{
	// Select points for a new connection.
	generateRandomConnection(input, output);

	// A connection can't go from itself to itself.
	if (input == output) return false;

	// Check if these nodes already have a connection.
	return connectionExists(input, output);
}

// Gets a random connection from the genome.
bool NeuralGenome::getRandomConnection(ConnectionGene** connectionGene)
{
	// Get a random connection gene.
	int connectionCount = connections.size();
	if (connectionCount == 0) return false;

	int connectionToSplit = rand() % connectionCount;
	*connectionGene = &connections[connectionToSplit].second;

	return true;
}

// Generates a random weight between -1.0 and 1.0
double NeuralGenome::randomWeight()
{
	return (((double)rand() / (RAND_MAX)) * 2.0) - 1.0;
}