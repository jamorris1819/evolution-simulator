#pragma once

#include <vector>
#include "triangle.h"

class PolygonData
{
public:
	PolygonData();
	~PolygonData();
	float* getVertices();
	void setVertices(std::vector<Vertex> data);
	std::vector<float> & getIndices();
	//void load();
	//void unload();
	int getVertexCount();
protected:
	std::vector<Vertex> vertices;
	std::vector<float> indices;
	void generateFloatData();
	int vertexCount;
	float* floatData;
};