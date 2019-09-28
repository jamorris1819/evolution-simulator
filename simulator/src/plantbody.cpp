#include "plantbody.h"
#include "contactlistener.h"
#define PI 3.14159265359

PlantBody::PlantBody(GLuint shader, b2World* world) : Body(shader, world)
{

}

void PlantBody::setAttributes(float size, float leafLength, int steps, int r, int g, int b)
{
	this->size = size;
	this->leafLength = leafLength;
	this->steps = steps;
	this->r = r;
	this->g = g;
	this->b = b;
}

void PlantBody::generateBodyPoints()
{
	if (rand() % 2 == 0) generateRoundBody();
	else generateSpikeyBody();
}

void PlantBody::generatePhysicsBody()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0.0f, 0.0f);
	physicsBody = world->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0); //position, relative to body position
	circleShape.m_radius = size / 2.0f; //radius

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;

	fixtureDef.filter.categoryBits = ContactType::PLANT;
	physicsBody->CreateFixture(&fixtureDef);
}

void PlantBody::generateRoundBody()
{
	steps = 30;
	double step = 2.0 * PI / steps;

	// Basic creature generation.
	vector<Vertex> vertices;

	// Generate the body.
	for (int i = 0; i < steps; i++) {
		Vertex v(glm::sin(i * step), glm::cos(i * step));
		float length = size;
		v.multiply(length);
		v.setColour(glm::vec3(r, g, b) / 255.0f);
		vertices.push_back(v);
	}

	// Assign these vertices to the polygon model.
	setVertices(vertices);
}

void PlantBody::generateSpikeyBody()
{
	size /= 3;
	steps = 16;
	double step = 2.0 * PI / steps;

	// Basic creature generation.
	vector<Vertex> vertices;

	// Generate the body.
	for (int i = 0; i < steps; i++) {
		Vertex v(glm::sin(i * step), glm::cos(i * step));
		float length = size + (i % 2 == 0 ? 0 : leafLength);
		v.multiply(length);
		v.setColour(glm::vec3(r, g, b) / 255.0f);
		vertices.push_back(v);
	}

	// Assign these vertices to the polygon model.
	setVertices(vertices);
}
