#include "netdata.h"

NetData::NetData()
{

}

void NetData::addNode(NodeData data)
{
	nodeData.push_back(data);
}

void NetData::addConnection(ConnectionData data)
{
	connectionData.push_back(data);
}


std::vector<NodeData> &NetData::getNodes()
{
	return nodeData;
}

std::vector<ConnectionData> &NetData::getConnections()
{
	return connectionData;
}