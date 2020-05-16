#include "pch.h"
#include "vertexarray.h"

VertexArray::VertexArray()
{
	floatData = nullptr;
	vertexCount = 0;
}

VertexArray::~VertexArray()
{
	if (floatData != nullptr) {
		delete floatData;
		floatData = nullptr;
	}
}

void VertexArray::generateFloatData() {
	if (floatData != nullptr) {
		delete floatData;
		floatData = nullptr;
	}

	// Put all vertex information into one large array, ready for use by OpenGL.
	int numOfProperties = 5;
	int numOfVertices = vertices.size();

	floatData = new float[numOfProperties * numOfVertices];

	for (int i = 0; i < numOfVertices; i++)
	{
		int offset = numOfProperties * i;

		Vertex v = vertices[i];

		floatData[offset] = v.getPosition().x;
		floatData[offset + 1] = v.getPosition().y;
		floatData[offset + 2] = v.getColour().x;
		floatData[offset + 3] = v.getColour().y;
		floatData[offset + 4] = v.getColour().z;
	}
}

void VertexArray::setVertices(std::vector<Vertex> const& data)
{
	vertices = data;
	for (unsigned short i = 0; i < vertices.size(); i++) indices.push_back(indices.size());
	generateFloatData();
}

void VertexArray::setData(std::vector<Vertex> const& vertices, std::vector<unsigned short> const& indices)
{
	this->vertices = vertices;
	this->indices = indices;

	generateFloatData();
}

float const* VertexArray::getVertices() const
{
	return floatData;
}

std::vector<unsigned short> const& VertexArray::getIndices() const
{
	return indices;
}

void VertexArray::setColour(glm::vec3 const& colour)
{
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].setColour(colour);
	}

	generateFloatData();
}

int VertexArray::getVertexCount() const {
	return vertices.size();
}

int VertexArray::getIndexCount() const {
	return indices.size();
}