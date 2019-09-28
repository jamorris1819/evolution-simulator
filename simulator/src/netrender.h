#pragma once
#include "netdata.h"

struct RConnection {
public:
	int from;
	int to;
	float weight;
	bool enabled;
};

struct RNode {
public:
	int x;
	int y;
	NodeType type;
};

struct RNet {
public:
	map<int, RConnection> connections;
	map<int, RNode> nodes;
};