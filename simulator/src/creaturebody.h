#pragma once
#include "vertexarray.h"
#include "genome.h"

class CreatureBody : public eng::VertexArray {
public:
	CreatureBody(Genome const& genome);
	void setNoiseOffset(float x, float y);
	void setNoiseParams(int steps, int noiseType, int octaves);
	virtual void generate();

protected:
	virtual void generateBodyPoints();
	void generateEyes();
	void generateMouth();

private:
	void extractGenomeData(Genome const& genome);
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