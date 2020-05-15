#include "pch.h"
#include "Triangle.h"
#include "glm/geometric.hpp"

Triangle::Triangle(Vertex a, Vertex b, Vertex c)
{
	setVertices(a, b, c);
	vertices[0].setColour(glm::vec3(1, 1, 1));
	vertices[1].setColour(glm::vec3(1, 1, 1));
	vertices[2].setColour(glm::vec3(1, 1, 1));
}

Triangle::~Triangle()
{
}

void Triangle::setVertices(Vertex v1, Vertex v2, Vertex v3)
{
	vertices[0] = v1;
	vertices[1] = v2;
	vertices[2] = v3;
}

void Triangle::setColour(glm::vec3 colour)
{
	this->colour = colour;
	vertices[0].setColour(colour);
	vertices[1].setColour(colour);
	vertices[2].setColour(colour);
}

Vertex* Triangle::getVertices()
{
	return vertices;
}

glm::vec3 Triangle::getColour() const
{
	return colour;
}

glm::vec2 Triangle::getCentre() const
{
	return glm::vec2(
		(vertices[0].getPosition().x + vertices[1].getPosition().x + vertices[2].getPosition().x) / 3.0f,
		(vertices[0].getPosition().y + vertices[1].getPosition().y + vertices[2].getPosition().y) / 3.0f
	);
}