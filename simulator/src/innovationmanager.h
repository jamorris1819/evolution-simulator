#pragma once
#include <vector>
#include <tuple>

class InnovationManager {
public:
	static int getInnovationNumber(int from, int to);
private:
	static std::vector<std::tuple<int, int>> connections;
	static int connectionInnovationCount;
	static int nodeInnovationCount;
};

std::vector<std::tuple<int, int>> InnovationManager::connections;

int InnovationManager::getInnovationNumber(int from, int to)
{
	for (int i = 0; i < connections.size(); i++) {
		std::tuple<int, int> connection = connections[i];

		// If it exists then this mutation has already occurred somewhere before.
		if (std::get<0>(connection) == from && std::get<1>(connection) == to)
			return i;
	}

	// If we reach here, then this is a new connection.
	int insertIndex = connections.size();
	connections.push_back(std::make_tuple(from, to));
	return insertIndex;
}