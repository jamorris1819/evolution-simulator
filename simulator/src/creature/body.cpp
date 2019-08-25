#include "body.h"
#include "noise\FastNoise.h"
#include "GL\glew.h"
#include "glm\glm.hpp"

#define PI 3.14159265359

Body::Body(GLuint shader, b2World* world) : PolygonR(shader)
{
	seed = 0;
	strideX = 1;
	strideY = 1;
	offsetX = 0;
	offsetY = 0;
	length = 1.0f;
	width = 1.0f;
	frequency = 0.25f;
	this->world = world;
}

Body::~Body()
{
}

void Body::addParameters(int steps, int noiseType, int octaves, float offsetX, float offsetY, int r, int g, int b)
{
	this->steps = steps;
	this->noiseType = noiseType;
	this->octaves = octaves;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	this->r = r;
	this->g = g;
	this->b = b;
}

glm::vec2 Body::getPosition()
{
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

void Body::generateBodyPoints()
{
	FastNoise noise;
	noise.SetSeed(seed);
	noise.SetNoiseType(FastNoise::SimplexFractal);
	noise.SetFractalOctaves(octaves);
	noise.SetFrequency(frequency);
	int sides = steps;
	double step = PI / sides;

	// Basic creature generation.
	vector<Vertex> vertices;

	// Generate half of the creature.
	for (int i = 0; i <= sides; i++) {
		Vertex v(glm::sin(i * step), glm::cos(i * step));
		float size = (noise.GetNoise((i * strideX) + offsetX, (i * strideY) + offsetY) + 1) / 2.0f;
		v.multiply(size);
		vertices.push_back(v);
	}

	// Copy and flip the vertices so they're mirrored.
	int size = vertices.size();
	for (int i = 1; i < size; i++) {
		Vertex v = vertices[size - i - 1];
		v.setPosition(glm::vec2(-1.0f, 1.0f) * v.getPosition());
		vertices.push_back(v);
	}

	// Scale body width length/width.
	for (int i = 0; i < vertices.size(); i++) {
		Vertex v = vertices[i];
		v.setPosition(glm::vec2(-width, length) * v.getPosition());
		v.setColour(glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f));
		vertices[i] = v;
	}

	// Assign these vertices to the polygon model.
	setVertices(vertices);
}

void Body::generatePhysicsBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(20.0f, 10.0f);
	physicsBody = world->CreateBody(&bodyDef);

	// Create the triangles for this body.
	for (int i = 0; i < vertices.size() - 1; i++) {
		// Get vertices.
		Vertex v1 = vertices[i];
		Vertex v2 = vertices[i + 1];
		b2Vec2 vert[3];

		// Assign shape's vertices.
		vert[0].Set(v1.getPosition().x, v1.getPosition().y);
		vert[1].Set(0.0f, 0.0f);
		vert[2].Set(v2.getPosition().x, v2.getPosition().y);
		
		b2PolygonShape shape;
		shape.Set(vert, 3);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 10.0f;
		fixtureDef.restitution = 0.6f;
		physicsBody->CreateFixture(&fixtureDef);
	}

	// Apply some settings to the new body.
	physicsBody->SetLinearDamping(2.0f);
	physicsBody->SetAngularDamping(5.0f);
}

void Body::unload()
{
	physicsBody->GetWorld()->DestroyBody(physicsBody);
}

void Body::moveForward(float power)
{
	float force = 60.0f * power;
	physicsBody->ApplyForceToCenter(
		b2Vec2(sin(-getRotation()) * force, cos(getRotation()) * force),
		true);
}

void Body::turnLeft()
{
	physicsBody->ApplyAngularImpulse(0.4f, true);
}

void Body::turnRight()
{
	physicsBody->ApplyAngularImpulse(-0.4f, true);
}