#include "pch.h"
#include "vertex.h"

Vertex::Vertex() : position(glm::vec2(0, 0)), colour(glm::vec3(1, 1, 1)) {}

Vertex::Vertex(glm::vec2 pos) : position(pos), colour(glm::vec3(1, 1, 1)) {}

Vertex::Vertex(float x, float y) : position(glm::vec2(x, y)), colour(glm::vec3(1, 1, 1)) {}

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

void Vertex::multiply(float scalar) {
	setPosition(glm::vec2(position.x * scalar, position.y * scalar));
}