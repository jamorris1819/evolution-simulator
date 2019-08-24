#pragma once
#include <vector>
#include "nodegene.h"

class NodeData {
public:
	int x;
	int y;
	NodeType type;
};

class ConnectionData {
public:
	int fx;
	int fy;
	int tx;
	int ty;
	float weight;
	bool enabled;
};

class NetData {
public:
	NetData();
	void addNode(NodeData data);
	void addConnection(ConnectionData data);
	std::vector<NodeData> getNodes();
	std::vector<ConnectionData> getConnections();
private:
	std::vector<NodeData> nodeData;
	std::vector<ConnectionData> connectionData;
};