#pragma once
#include "../render/polygon.h"

class Body : public PolygonR {
public:
	Body(GLuint shader);
	~Body();
	void addParameters(int steps, int noiseType, int octaves, float offsetX, float offsetY, int r, int g, int b);
	void generate();
	int seed;
	int steps;
	int noiseType;
	int octaves;
	int strideX;
	int strideY;
	float offsetX;
	float offsetY;
	float length;
	float width;
	float frequency;
	int r;
	int g;
	int b;
};