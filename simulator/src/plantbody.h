#pragma once
#include "body.h"

class PlantBody : public Body {
public:
	PlantBody(GLuint shader, b2World* world);
	void setAttributes(float size, float leafLength, int steps, int r, int g, int b);
private:
	virtual void generateBodyPoints();
	virtual void generatePhysicsBody();
	void generateRoundBody();
	void generateSpikeyBody();
	float size;
	float leafLength;
	int steps;
};