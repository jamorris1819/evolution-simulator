#include "plantbody.h"
#include "contactlistener.h"
#include <poisson_disk_sampling.h>
#define PI 3.14159265359
/*
PlantBody::PlantBody(GLuint shader, b2World* world) {
	leafLayers = 3;
	leafLength = 1;
	bushCount = 5;
	size = 1;
	steps = 10;
}

void PlantBody::setAttributes(float size, float leafLength, int leafLayers, int steps, int bushCount, int r, int g, int b) {
	this->size = size;
	this->leafLength = leafLength;
	this->leafLayers = leafLayers;
	this->bushCount = bushCount;
	this->steps = steps;
	//this->r = r;
	///this->g = g;
	//this->b = b;
}

void PlantBody::generatePhysicsBody() {
	/*b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(0.0f, 0.0f);
	physicsBody = world->CreateBody(&bodyDef);

	b2CircleShape circleShape;
	circleShape.m_p.Set(0, 0); //position, relative to body position
	circleShape.m_radius = size; //radius

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circleShape;

	fixtureDef.filter.categoryBits = ContactType::PLANT;
	physicsBody->CreateFixture(&fixtureDef);
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
}*/