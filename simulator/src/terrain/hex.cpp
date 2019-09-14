#include "hex.h"
#include <glm\ext\matrix_transform.hpp>

#define PI 3.14159265359

Hex::Hex(glm::vec2 position, GLuint program) : PolygonR(program)
{
	generate();
	load();
	this->position = glm::vec3(position, 0);
}

void Hex::generate()
{
	vector<Vertex> vertices;
	for (int i = 0; i < 6; i++) {
		float angle_deg = 60 * i - 30;
		float angle_rad = PI / 180 * angle_deg;
		Vertex v(cos(angle_rad), sin(angle_rad));
		v.setColour(glm::vec3(1, 0, 0));
		vertices.push_back(v);
	}

	setVertices(vertices);
}

void Hex::render()
{
	PolygonR::render(glm::translate(glm::mat4(1.0f), position));
}
