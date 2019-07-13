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
			ConnectionGene connectionGene(i, inputs + j, true, 0.5f, connections.size());
			connections.insert(std::make_pair(connections.size(), connectionGene));
		}
	}

	inputCount = inputs;
	outputCount = outputs;
}

float* NeuralGenome::evaluate(float* inputs)
{
	float* outputs = new float[outputCount];

	for (int i = 0; i < outputCount; i++) {
		outputs[i] = recurseNetwork(inputCount + i, inputs);
	}

	return outputs;
}

float NeuralGenome::recurseNetwork(int node, float *inputs)
{
	float toReturn = 0.0f;

	std::map<int, ConnectionGene>::iterator it;
	std::vector<ConnectionGene> genes;

	for (it = connections.begin(); it != connections.end(); it++)
	{
		ConnectionGene connGene = it->second;
		if (connGene.getOutputNode() == node) genes.push_back(connGene);
	}

	for (int i = 0; i < genes.size(); i++) {
		ConnectionGene connGene = genes[i];
		int attachedNode = connGene.getInputNode();

		// If less than input count then it's an input node.
		if (attachedNode < inputCount) {
			toReturn += inputs[attachedNode] * connGene.getWeight();
			continue;
		}
		
		// If it's a hidden node then we must recurse further.
		toReturn += recurseNetwork(attachedNode, inputs) * connGene.getWeight();
	}

	return toReturn;
}

