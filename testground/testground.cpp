// testground.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "vertexarray.h"
#include <vector>

void printv(eng::Vertex const& v) {
	std::cout << v.getPosition().x << ", " << v.getPosition().y << std::endl;
}

void printva(eng::VertexArray& v) {
	printv(v.getVertices()[0]);
}

int main() {
	eng::VertexArray v1;

	{
		std::vector<eng::Vertex> tmp;
		eng::Vertex v;
		v.setPosition(glm::vec2(1, 2));
		tmp.push_back(v);

		v1.setVertices(tmp);
	}

	eng::VertexArray v2;

	{
		std::vector<eng::Vertex> tmp;
		eng::Vertex v;
		v.setPosition(glm::vec2(3, 4));
		tmp.push_back(v);

		v2.setVertices(tmp);
	}

	printva(v1);
	printva(v2);

	v2 = v1;

	printva(v1);
	printva(v2);

	{
		std::vector<eng::Vertex> tmp;
		eng::Vertex v;
		v.setPosition(glm::vec2(3, 4));
		tmp.push_back(v);

		v2.setVertices(tmp);
	}

	printva(v1);
	printva(v2);

	while (true) {
		eng::Vertex va;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file