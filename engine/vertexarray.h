#pragma once

#include <vector>
#include "triangle.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void setVertices(std::vector<Vertex> const& data);
	void setData(std::vector<Vertex> const& vertices, std::vector<unsigned short> const& indices);
	float const* getVertices() const;
	std::vector<unsigned short> const& getIndices() const;
	void setColour(glm::vec3 const& colour);
	int getVertexCount() const;
	int getIndexCount() const;
protected:
	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;
	void generateFloatData();
	int vertexCount;
	float* floatData;
};