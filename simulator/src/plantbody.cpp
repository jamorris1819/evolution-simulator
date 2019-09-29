#include "plantbody.h"
#include "contactlistener.h"
#include <poisson_disk_sampling.h>
#define PI 3.14159265359

PlantBody::PlantBody(GLuint shader, b2World* world) : Body(shader, world)
{
	leafLayers = 3;
	leafLength = 1;
	bushCount = 5;
	size = 1;
	steps = 10;
}

void PlantBody::setAttributes(float size, float leafLength, int leafLayers, int steps, int bushCount, int r, int g, int b)
{
	this->size = size;
	this->leafLength = leafLength;
	this->leafLayers = leafLayers;
	this->bushCount = bushCount;
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

	int numberOfCircles = bushCount;
	float angleStep = PI * 2.0 / (float)numberOfCircles;

	// Shrink the vertices down to be reused for the additional polygons.
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].setPosition(vertices[i].getPosition() * glm::vec2(0.75, 0.75));
	}

	// Generate some extra 'bumps' around these to make them look bush-like.
	// Iterate around in a circular fashion.
	for (int i = 0; i < numberOfCircles; i++) {
		PolygonR* p = new PolygonR(shaderID);
		vector<Vertex> subVertices;

		for (int j = 0; j < vertices.size(); j++) {
			Vertex& v = vertices[j];

			// Allow the vertices to fluctuate randomly to give it a rougher look.
			float multiplier = 1.0f - ((rand() % 25) / 100.0f);

			// Get new position.
			float x = cos(i * angleStep) * size * multiplier;
			float y = sin(i * angleStep) * size * multiplier;

			// Create new vertex.
			Vertex nV(x + v.getPosition().x, y + v.getPosition().y);
			nV.setColour(v.getColour());
			subVertices.push_back(nV);
		}
		p->setVertices(subVertices);
		p->load();
		polygons.push_back(p);
	}

	// Shrink the vertices down to be reused for the additional polygons.
	float fruitScale = 1.0f + (rand() % 10) / 10.0f;
	for (int i = 0; i < vertices.size(); i++) {
		vertices[i].setPosition(vertices[i].getPosition() * 0.1f * fruitScale);
	}

	namespace pds = thinks::poisson_disk_sampling;
	auto radius = fruitScale * 0.75f * 0.5f;
	const auto x_min = std::array<float, 2>{ { -size, -size }};
	const auto x_max = std::array<float, 2>{ { size, size }};

	// Samples returned as std::vector<std::array<float, 2>>.
	// Default seed and max attempts.
	std::vector<std::array<float, 2>> samples = pds::PoissonDiskSampling(radius, x_min, x_max, 30U, rand());

	for (int i = 0; i < samples.size(); i++) {
		std::array<float, 2> sample = samples[i];

		PolygonR* p = new PolygonR(shaderID);
		vector<Vertex> subVertices;

		for (int j = 0; j < vertices.size(); j++) {
			Vertex& v = vertices[j];


			// Create new vertex.
			Vertex nV(0, 0);
			nV.setPosition(v.getPosition() + glm::vec2(sample[0], sample[1]));
			nV.setColour(glm::vec3(1, 0, 0));
			subVertices.push_back(nV);
		}
		p->setVertices(subVertices);
		p->load();
		polygons.push_back(p);
	}
}

void PlantBody::generateSpikeyBody()
{
	size /= 3;
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

	// Body has been generated. Now add extra polygon layers.
	float angleStep = 360.0f / (float)leafLayers;

	for (int i = 1; i < leafLayers; i++) {
		PolygonR* p = new PolygonR(shaderID);
		for (int j = 0; j < vertices.size(); j++) {
			Vertex& v = vertices[j];
			float s = sin(angleStep);
			float c = cos(angleStep);

			// rotate point
			float xnew = v.getPosition().x * c - v.getPosition().y * s;
			float ynew = v.getPosition().x * s + v.getPosition().y * c;

			// translate point back:
			v.setPosition(glm::vec2(xnew, ynew) * 0.85f);
			v.setColour(v.getColour() * (glm::vec3(1.0f, 1.1f, 1.0f)));
		}
		p->setVertices(vertices);
		p->load();
		polygons.push_back(p);
	}
}
