#pragma once

#include <vector>
#include "triangle.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	float* getVertices();
	void setVertices(std::vector<Vertex> data);
	void setData(std::vector<Vertex> vertices, std::vector<short> indices);
	std::vector<short>& getIndices();
	void setColour(glm::vec3 colour);
	int getVertexCount();
protected:
	std::vector<Vertex> vertices;
	std::vector<short> indices;
	void generateFloatData();
	int vertexCount;
	float* floatData;
};