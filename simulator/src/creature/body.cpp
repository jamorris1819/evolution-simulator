#include "body.h"
#include "noise\FastNoise.h"
#include "GL\glew.h"
#include "glm\glm.hpp"

#define PI 3.14159265359

Body::Body(GLuint shader, b2World* world) : PolygonR(shader)
{
	seed = 0;
	this->world = world;
}

Body::~Body()
{
}

glm::vec2 Body::getPosition()
{
	if (physicsBody == nullptr) return glm::vec2(0, 0);
	b2Vec2 position = physicsBody->GetPosition();
	return glm::vec2(position.x, position.y);
}

float Body::getRotation()
{
	return physicsBody->GetAngle();
}

void Body::setPosition(glm::vec2 position)
{
	physicsBody->SetTransform(b2Vec2(position.x, position.y), physicsBody->GetAngle());
}

void Body::setRotation(float rotation)
{
	physicsBody->SetTransform(physicsBody->GetPosition(), rotation);
}

b2Body* Body::getPhysicsBody()
{
	return physicsBody;
}

void Body::generate()
{
	// Generate the shape of the body.
	generateBodyPoints();

	// Generate physics body.
	generatePhysicsBody();
}

void Body::unload()
{
	physicsBody->GetWorld()->DestroyBody(physicsBody);
}

void Body::moveForward(float power)
{
	float force = 600.0f * power;
	physicsBody->ApplyForceToCenter(
		b2Vec2(sin(-getRotation()) * force, cos(getRotation()) * force),
		true);
}

void Body::turnLeft(float power)
{
	physicsBody->ApplyAngularImpulse(power, true);
}

void Body::turnRight(float power)
{
	physicsBody->ApplyAngularImpulse(power, true);
}

void Body::render(glm::mat4 matrix)
{
	PolygonR::render(matrix);

	for (int i = 0; i < polygons.size(); i++) {
		polygons[i]->render(matrix);
	}
}

void Body::setRGB(int r, int g, int b)
{
	this->r = r;
	this->g = g;
	this->b = b;
}