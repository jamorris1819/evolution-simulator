#include "polygonData.h"



PolygonData::PolygonData()
{
	floatData = nullptr;
}


PolygonData::~PolygonData()
{
}

void PolygonData::generateFloatData() {
	if (floatData != nullptr) delete floatData;

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

void PolygonData::setVertices(std::vector<Vertex> data)
{
	vertices = data;
	for (int i = 0; i < vertices.size(); i++) indices.push_back(indices.size());
	generateFloatData();
}

float* PolygonData::getVertices()
{
	return floatData;
}

std::vector<float>& PolygonData::getIndices()
{
	return indices;
}

int PolygonData::getVertexCount() {
	return vertices.size();
}