#include "pch.h"
#include "vertex.h"

Vertex::Vertex() {
	setDefault();
}

Vertex::~Vertex() {
	setDefault();
}

Vertex::Vertex(float x, float y) {
	setPosition(glm::vec2(x, y));
	setColour(glm::vec3(1, 0, 0));
}

Vertex::Vertex(glm::vec2 position) {
	setPosition(position);
}

glm::vec2 const& Vertex::getPosition() const {
	return position;
}

glm::vec3 const& Vertex::getColour() const {
	return colour;
}

void Vertex::setPosition(glm::vec2 data) {
	position = data;
}

void Vertex::setColour(glm::vec3 const& data) {
	colour = data;
}

void Vertex::setDefault() {
	glm::vec3 zero(0, 0, 0);
	glm::vec3 one(1, 1, 1);
	setPosition(zero);
	setColour(one);
}

void Vertex::multiply(float scalar) {
	setPosition(glm::vec2(position.x * scalar, position.y * scalar));
}