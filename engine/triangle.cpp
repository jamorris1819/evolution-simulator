#include "pch.h"
#include "Triangle.h"
#include "glm/geometric.hpp"

Triangle::Triangle(Vertex const& v1, Vertex const& v2, Vertex const& v3) {
	setVertices(v1, v2, v3);
	vertices[0].setColour(glm::vec3(1, 1, 1));
	vertices[1].setColour(glm::vec3(1, 1, 1));
	vertices[2].setColour(glm::vec3(1, 1, 1));
}

Triangle::~Triangle() {
}

void Triangle::setVertices(Vertex const& v1, Vertex const& v2, Vertex const& v3) {
	vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;
}

void Triangle::setColour(glm::vec3 const& colour) {
	this->colour = colour;
	vertices[0].setColour(colour);
	vertices[1].setColour(colour);
	vertices[2].setColour(colour);
}

Vertex const* Triangle::getVertices() const {
	return vertices;
}

glm::vec3 const& Triangle::getColour() const {
	return colour;
}

glm::vec2 const& Triangle::getCentre() const {
	return glm::vec2(
		(vertices[0].getPosition().x + vertices[1].getPosition().x + vertices[2].getPosition().x) / 3.0f,
		(vertices[0].getPosition().y + vertices[1].getPosition().y + vertices[2].getPosition().y) / 3.0f
	);
}