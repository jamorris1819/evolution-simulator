#define e 2.71828

#include "neuralgenome.h"
#include <vector>

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
	for (int i = 0; i < inputs; i++) {
		for (int j = 0; j < outputs; j++) {
			bool enabled = true;
			ConnectionGene connectionGene(i, inputs + j, enabled, ((((double)rand() / (RAND_MAX)) + 1.0) * 2.0) - 1.0, connections.size());
			connections.insert(std::make_pair(connections.size(), connectionGene));
		}
	}

	inputCount = inputs;
	outputCount = outputs;

	// Add hidden node.
	/*NodeGene nodeGene(NodeType::HIDDEN);
	nodes.insert(std::make_pair(nodes.size(), nodeGene));

	ConnectionGene connectionGene(3, inputCount + outputCount, true, ((((double)rand() / (RAND_MAX)) + 1.0) * 2.0) - 1.0, connections.size());
	connections.insert(std::make_pair(connections.size(), connectionGene));

	ConnectionGene connectionGene2(1, inputCount + outputCount, true, ((((double)rand() / (RAND_MAX)) + 1.0) * 2.0) - 1.0, connections.size());
	connections.insert(std::make_pair(connections.size(), connectionGene2));

	ConnectionGene connectionGene0(0, inputCount + outputCount, true, ((((double)rand() / (RAND_MAX)) + 1.0) * 2.0) - 1.0, connections.size());
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
			toReturn += inputs[attachedNode] * connGene.getWeight();
			continue;
		}
		
		// If it's a hidden node then we must recurse further.
		toReturn += recurseNetwork(attachedNode, inputs) * connGene.getWeight();
	}

	return sigmoid(toReturn);
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