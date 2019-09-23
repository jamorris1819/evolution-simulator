#pragma once
#include "../render/polygon.h"
#include "Box2D\Box2D.h"
#include "glm\vec2.hpp"
#include <vector>

class Body : public PolygonR {
public:
	Body(GLuint shader, b2World* world);
	~Body();
	void unload();
	glm::vec2 getPosition();
	float getRotation();
	void setPosition(glm::vec2 position);
	void setRotation(float rotation);
	b2Body* getPhysicsBody();

	void moveForward(float power);
	void turnLeft(float power);
	void turnRight(float power);
	void render(glm::mat4 matrix);
	//virtual void update() = 0;

	void setRGB(int r, int g, int b);

	virtual void generate();
	int seed;
	
	int r;
	int g;
	int b;

protected:
	std::vector<PolygonR*> polygons;
	virtual void generateBodyPoints() = 0;
	virtual void generatePhysicsBody();
	b2Body* physicsBody;
	b2World* world;
};