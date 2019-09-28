#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

class Vertex
{
public:
	Vertex();
	Vertex(float x, float y);
	Vertex(glm::vec2 position);
	~Vertex();
	const glm::vec2 & getPosition() const;
	void setPosition(glm::vec2 data);
	const glm::vec3 & getColour() const;
	void setColour(glm::vec3 data);
	void multiply(float scalar);
	void setDefault();

private:
	glm::vec2 position;
	glm::vec3 colour;
};

