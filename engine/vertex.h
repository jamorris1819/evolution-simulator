#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

class Vertex {
public:
	Vertex();
	Vertex(float x, float y);
	Vertex(glm::vec2 pos);
	glm::vec2 const& getPosition() const;
	glm::vec3 const& getColour() const;
	void setPosition(glm::vec2 data);
	void setColour(glm::vec3 const& data);
	void multiply(float scalar);

private:
	glm::vec2 position;
	glm::vec3 colour;
};
