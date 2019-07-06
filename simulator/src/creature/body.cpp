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

void Body::setPosition(glm::vec2 position)
{
	physicsBody->SetTransform(b2Vec2(position.x, position.y), physicsBody->GetAngle());
}

void Body::generate()
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
		v.multiply(80.0f);
		v.multiply(size);
		vertices.push_back(v);
	}

	// Copy and flip the vertices so they're mirrored.
	int size = vertices.size();
	for (int i = 0; i < size; i++) {
		Vertex v = vertices[size - i - 1];
		v.setPosition(glm::vec2(-1.0f, 1.0f) * v.getPosition());
		vertices.push_back(v);
	}
	//offsetX += 0.01f;
	//offsetY += 0.01f;

	// Scale body width length/width.

	for (int i = 0; i < vertices.size(); i++) {
		Vertex v = vertices[i];
		v.setPosition(glm::vec2(-width, length) * v.getPosition());
		v.setColour(glm::vec3(r / 255.0f, g / 255.0f, b / 255.0f));
		vertices[i] = v;
	}

	setVertices(vertices);




	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(300.0f, 500.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);







	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(300.0f, 300.0f);
	physicsBody = world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 10.0f;

	// Override the default friction.
	fixtureDef.friction = 10.0f;

	// Add the shape to the body.
	physicsBody->CreateFixture(&fixtureDef);
	physicsBody->SetLinearDamping(1.0f);
}