#pragma once

#include <vector>
#include <iostream>
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "vertex.h"

class Triangle {
public:
	Triangle(Vertex const& v1, Vertex const& v2, Vertex const& v3);
	~Triangle();
	Vertex const* getVertices() const;
	void setVertices(Vertex const& v1, Vertex const& v2, Vertex const& v3);
	void setColour(glm::vec3 const& colour);
	glm::vec3 const& getColour() const;
	glm::vec2 const& getCentre() const;
private:
	Vertex vertices[3];
	glm::vec3 colour;
};
