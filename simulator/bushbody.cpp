#include "bushbody.h"
#include <glm\trigonometric.hpp>
#include <poisson_disk_sampling.h>
#define PI 3.14159265359

BushBody::BushBody(GLuint shader, b2World* world) : PlantBody(shader, world) {
}

void BushBody::generateBodyPoints() {
	/*steps = 30;
	double step = 2.0 * PI / steps;

	// Basic creature generation.
	vector<eng::Vertex> vertices;

	// Generate the body.
	for (int i = 0; i < steps; i++) {
		eng::Vertex v(glm::sin(i * step), glm::cos(i * step));
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
		eng::VertexRenderer* p = new eng::VertexRenderer(shaderID);
		vector<eng::Vertex> subVertices;

		for (int j = 0; j < vertices.size(); j++) {
			eng::Vertex& v = vertices[j];

			// Allow the vertices to fluctuate randomly to give it a rougher look.
			float multiplier = 1.0f - ((rand() % 25) / 100.0f);

			// Get new position.
			float x = cos(i * angleStep) * size * multiplier;
			float y = sin(i * angleStep) * size * multiplier;

			// Create new vertex.
			eng::Vertex nV(x + v.getPosition().x, y + v.getPosition().y);
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

		VertexRenderer* p = new VertexRenderer(shaderID);
		vector<eng::Vertex> subVertices;

		for (int j = 0; j < vertices.size(); j++) {
			eng::Vertex& v = vertices[j];

			// Create new vertex.
			eng::Vertex nV(0, 0);
			nV.setPosition(v.getPosition() + glm::vec2(sample[0], sample[1]));
			nV.setColour(glm::vec3(1, 0, 0));
			subVertices.push_back(nV);
		}
		p->setVertices(subVertices);
		p->load();
		p->setVisible(false);
		fruit.push_back(p);
		polygons.push_back(p);
	}*/
}

void BushBody::setVisibleFruit(int i) {
	for (int j = 0; j < fruit.size(); j++) {
		fruit[j]->setVisible(j < i);
	}
}