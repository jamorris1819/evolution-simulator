#pragma once
#include "body.h"

class CreatureBody : public Body {
public:
	CreatureBody(GLuint shader, b2World* world);
	void setNoiseOffset(float x, float y);
	void setNoiseParams(int steps, int noiseType, int octaves);
	virtual void generate();
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

protected:
	virtual void generateBodyPoints();
	virtual void generatePhysicsBody();
	void generateEyes();
	void generateMouth();
};