#define e 2.71828

#include "neuralgenome.h"
#include <vector>

int NeuralGenome::innovationNumber = 0;


NeuralGenome::NeuralGenome(int inputs, int outputs)
{
	// Create input nodes.
	for (int i = 0; i < inputs; i++) {
		NodeGene nodeGene(NodeType::INPUT);
		nodes.insert(std::make_pair(nodes.size(), nodeGene));
	}

	// Create output nodes.
	for (int i = 0; i < outputs; i++) {
		NodeGene nodeGene(NodeType::OUTPUT);
		nodes.insert(std::make_pair(nodes.size(), nodeGene));
	}

	// Create connections.
	/*for (int i = 0; i < inputs; i++) {
		for (int j = 0; j < outputs; j++) {
			bool enabled = i != 0;
			double weight = 1.0;// (((double)rand() / (RAND_MAX)) * 2.0) - 1.0;
			ConnectionGene connectionGene(i, inputs + j, enabled, weight, connections.size());
			connections.insert(std::make_pair(connections.size(), connectionGene));
		}
	}*/

	inputCount = inputs;
	outputCount = outputs;

	// Add hidden node.
	/*NodeGene nodeGene(NodeType::HIDDEN);
	nodes.insert(std::make_pair(nodes.size(), nodeGene));

	ConnectionGene connectionGene(0, 2, true, -1.0, connections.size());
	connections.insert(std::make_pair(connections.size(), connectionGene));

	ConnectionGene connectionGene2(2, 1, true, 1.0, connections.size());
	connections.insert(std::make_pair(connections.size(), connectionGene2));

	/*ConnectionGene connectionGene0(0, inputCount + outputCount, true, ((((double)rand() / (RAND_MAX)) + 1.0) * 2.0) - 1.0, connections.size());
	connections.insert(std::make_pair(connections.size(), connectionGene0));

	ConnectionGene connectionGene20(2, inputCount + outputCount, true, ((((double)rand() / (RAND_MAX)) + 1.0) * 2.0) - 1.0, connections.size());
	connections.insert(std::make_pair(connections.size(), connectionGene20));

	ConnectionGene connectionGene3(inputCount + outputCount, inputCount + outputCount - 1, true, ((((double)rand() / (RAND_MAX)) + 1.0) * 2.0) - 1.0, connections.size());
	connections.insert(std::make_pair(connections.size(), connectionGene3));*/
	
}

float* NeuralGenome::evaluate(float* inputs)
{
	float* outputs = new float[outputCount];

	for (int i = 0; i < outputCount; i++) {
		outputs[i] = recurseNetwork(inputCount + i, inputs);
	}

	return outputs;
}

float sigmoid(float x) {
	return (1 / (1 + pow(e, -x)));
}

float NeuralGenome::recurseNetwork(int node, float *inputs)
{
 	float toReturn = 0.0f;

	std::map<int, ConnectionGene>::iterator it;
	std::vector<ConnectionGene> genes;

	for (it = connections.begin(); it != connections.end(); it++)
	{
		ConnectionGene connGene = it->second;
		if (connGene.getOutputNode() == node)
			genes.push_back(connGene);
	}

	for (int i = 0; i < genes.size(); i++) {
		ConnectionGene connGene = genes[i];
		int attachedNode = connGene.getInputNode();

		// If disabled then skip.
		if (!connGene.getEnabled()) continue;

		// If less than input count then it's an input node.
		if (attachedNode < inputCount) {
			double val = inputs[attachedNode] * connGene.getWeight();
			toReturn += val;

			nodes.at(attachedNode).setValue(inputs[attachedNode]);
			continue;
		}
		
		// If it's a hidden node then we must recurse further.
		toReturn += sigmoid(recurseNetwork(attachedNode, inputs) * connGene.getWeight());
	}

	float value = sigmoid(toReturn);
	nodes.at(node).setValue(value);
	return value;
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

bool NeuralGenome::tryAddConnection(int& fromNode, int& toNode)
{
	bool hiddenNodesExist = getNodeCount() > inputCount + outputCount;	// If there are hidden nodes in this neural network.
	bool useHiddenNode = hiddenNodesExist && rand() % 2 == 0;			// If we want to involve a hidden node in this connection.

	if (useHiddenNode) {
		bool startOnHidden = rand() % 2 == 0;
		int hiddenNodeCount = getNodeCount() - inputCount - outputCount;
		int hiddenNodeToUse = rand() % hiddenNodeCount;

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

	double weight = (((double)rand() / (RAND_MAX)) * 2.0) - 1.0;

	// Create the connection
	ConnectionGene gene(fromNode, toNode, true, weight, 0);
	connections.insert(std::make_pair(connections.size(), gene));
}