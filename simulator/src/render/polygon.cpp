#include "polygon.h"



Polygon::Polygon()
{
	floatData = nullptr;
}


Polygon::~Polygon()
{
}

void Polygon::setVertices(std::vector<Vertex> data)
{
	Vertex v1(0.0f, 0.0f);
	Vertex v2(0.5f, 1.0f);
	Vertex v3(1.0f, 0.0f);
	Triangle t(v1, v2, v3);

	std::vector<Triangle> tris;
	tris.push_back(t);
	triangles = tris;
}

float* Polygon::getVertices()
{
	if (floatData == nullptr) {
		// Put all vertex information into one large array, ready for use by OpenGL.
		int numOfProperties = 9;
		int numOfTriangles = triangles.size();

		floatData = new float[numOfProperties * numOfTriangles * 3];

		for (int i = 0; i < numOfTriangles; i++)
		{

			int baseOffset = numOfProperties * i * 3;
			for (int j = 0; j < 3; j++)
			{
				int fineOffset = numOfProperties * j;
				int overallOffset = baseOffset + fineOffset;

				Vertex v = triangles[i].getVertices()[j];

				floatData[overallOffset] = v.getPosition().x;
				floatData[overallOffset + 1] = v.getPosition().y;
				floatData[overallOffset + 2] = v.getColour().x;
				floatData[overallOffset + 3] = v.getColour().y;
				floatData[overallOffset + 4] = v.getColour().z;
			}
		}
	}

	return floatData;
}

std::vector<float>& Polygon::getIndices()
{
	return indices;
}

int Polygon::getVertexCount() {
	return vertices.size();
}