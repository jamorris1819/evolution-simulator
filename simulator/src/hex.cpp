#include "hex.h"
#include <glm\ext\matrix_transform.hpp>

#define PI 3.14159265359

Hex::Hex(int size, glm::vec2 position, GLuint program) : PolygonData(program) {
	this->size = size;
	generate();
	load();
	this->position = glm::vec3(position, 0);
	fade = false;
	fadeOffset = rand() % 360;
}

void Hex::generate() {
	Vertex origin(0, 0);
	origin.setColour(glm::vec3(1, 0, 0));
	vector<Vertex> vertices;

	vertices.push_back(origin);

	for (int i = 0; i < 6; i++) {
		float angle_deg = 60 * i - 30;
		float angle_rad = PI / 180 * angle_deg;
		Vertex v(cos(angle_rad) * size, sin(angle_rad) * size);
		v.setColour(glm::vec3(1, 0, 0));
		vertices.push_back(v);
	}

	vector<unsigned short> indices{
		1, 0, 2, 2, 0, 3, 3, 0, 4, 4, 0, 5, 5, 0, 6, 6, 0, 1
	};

	setData(vertices, indices);
}

void Hex::render() {
	PolygonData::render(glm::translate(glm::mat4(1.0f), position));
}

void Hex::update(double deltaTime) {
	if (fade) {
		if (time == 0) colour = overrideColour;
		time += deltaTime;
		float c = (6.0f * sin(time + fadeOffset)) + 3.0f;
		overrideColour = colour + (glm::vec3(c, c, c) / 255.0f);
	}
}

bool Hex::getFade() {
	return fade;
}

void Hex::setFade(bool fade) {
	this->fade = fade;
}

int Hex::getFadeOffset() {
	return fadeOffset;
}

void Hex::setFadeOffset(int fadeOffset) {
	this->fadeOffset = fadeOffset;
}