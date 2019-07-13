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
	void resetTemp();
private:
	double tempValue;
	bool useTemp;
	NodeType nodeType;
};