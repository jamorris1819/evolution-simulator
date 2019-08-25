#pragma once

enum class NodeType
{
	INPUT,
	OUTPUT,
	HIDDEN
};

class NodeGene {
public:
	NodeGene(NodeType type);
	~NodeGene();
	NodeType getType();
	double getValue();
	void setValue(double val);
private:
	double tempValue;
	bool useTemp;
	NodeType nodeType;
};