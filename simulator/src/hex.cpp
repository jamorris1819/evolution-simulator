#include "hex.h"
#include <glm\ext\matrix_transform.hpp>

#define PI 3.14159265359

Hex::Hex(int size, glm::vec2 position, GLuint program) : PolygonR(program)
{
	this->size = size;
	generate();
	load();
	this->position = glm::vec3(position, 0);
	fade = false;
	fadeOffset = rand() % 360;
}

void Hex::generate()
{
	vector<Vertex> vertices;
	for (int i = 0; i < 6; i++) {
		float angle_deg = 60 * i - 30;
		float angle_rad = PI / 180 * angle_deg;
		Vertex v(cos(angle_rad) * size, sin(angle_rad) * size);
		v.setColour(glm::vec3(1, 0, 0));
		vertices.push_back(v);
	}

	setVertices(vertices);
}

void Hex::render()
{
	PolygonR::render(glm::translate(glm::mat4(1.0f), position));
}

void Hex::update(double deltaTime)
{
	if (fade) {
		if (time == 0) colour = overrideColour;
		time += deltaTime;
		float c = (6.0f * sin(time + fadeOffset)) + 3.0f;
		overrideColour =  colour + (glm::vec3(c, c, c) / 255.0f);
	}
}

bool Hex::getFade()
{
	return fade;
}

void Hex::setFade(bool fade)
{
	this->fade = fade;
}

int Hex::getFadeOffset()
{
	return fadeOffset;
}

void Hex::setFadeOffset(int fadeOffset)
{
	this->fadeOffset = fadeOffset;
}
