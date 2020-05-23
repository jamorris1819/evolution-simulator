#pragma once
#include "polygon.h"
#include "body.h"
#include "genome.h"

class CreatureBody: public Body {
public:
	CreatureBody(Genome* genome);
	void setNoiseOffset(float x, float y);
	void setNoiseParams(int steps, int noiseType, int octaves);
	virtual void generate() override;

protected:
	virtual void generateBodyPoints();
	void generateEyes();
	void generateMouth();

private:
	void extractGenomeData(Genome* genome);
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