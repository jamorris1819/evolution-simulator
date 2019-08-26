#pragma once

enum class NodeType
{
	INPUT,
	OUTPUT,
	HIDDEN
};

enum class ActivationFunction
{
	SIGMOID,
	RELU,
	NONE
};

class NodeGene {
public:
	NodeGene(NodeType type);
	~NodeGene();
	NodeType getType();
	double getValue();
	void setValue(double val);
	ActivationFunction getActivationFunction();
	void setActivationFunction(ActivationFunction activationFunction);
private:
	double tempValue;
	bool useTemp;
	NodeType nodeType;
	ActivationFunction activationFunction;
};