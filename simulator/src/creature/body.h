#pragma once
#include "../render/polygon.h"
#include "Box2D\Box2D.h"
#include "glm\vec2.hpp"
#include <vector>

class Body : public PolygonR {
public:
	Body(GLuint shader, b2World* world);
	~Body();
	void addParameters(int steps, int noiseType, int octaves, float offsetX, float offsetY, int r, int g, int b);
	void unload();
	glm::vec2 getPosition();
	float getRotation();
	void setPosition(glm::vec2 position);
	void setRotation(float rotation);
	b2Body* getPhysicsBody();

	void moveForward(float power);
	void turnLeft();
	void turnRight();
	void update();

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

private:
	void generateBodyPoints();
	void generatePhysicsBody();
	void generateMouth();
	b2Body* physicsBody;
	b2World* world;
};