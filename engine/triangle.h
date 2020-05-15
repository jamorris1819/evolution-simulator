#pragma once

#include <vector>
#include <iostream>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "vertex.h"

class Triangle
{
public:
	Triangle(Vertex a, Vertex b, Vertex c);
	Vertex* getVertices();
	void setVertices(Vertex v1, Vertex v2, Vertex v3);
	void setColour(glm::vec3 colour);
	glm::vec3 getColour() const;
	glm::vec2 getCentre() const;
	~Triangle();
private:
	Vertex vertices[3];
	glm::vec3 colour;
};
