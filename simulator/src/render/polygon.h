#pragma once

#include <vector>
#include "triangle.h"

class Polygon
{
public:
	Polygon();
	~Polygon();
	float* getVertices();
	void setVertices(std::vector<Vertex> data);
	std::vector<float> & getIndices();
	//void load();
	//void unload();
	int getVertexCount();
protected:
	std::vector<Triangle> triangles;
	std::vector<Vertex> vertices;
	std::vector<float> indices;
	int vertexCount;
	float* floatData;
};