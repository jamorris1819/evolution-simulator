#include "pch.h"
#include "vertex.h"

namespace engine {
	Vertex::Vertex() : position(glm::vec2(0, 0)), colour(glm::vec3(1, 1, 1)) {}

	Vertex::Vertex(glm::vec2 pos) : position(pos), colour(glm::vec3(1, 1, 1)) {}

	Vertex::Vertex(float x, float y) : position(glm::vec2(x, y)), colour(glm::vec3(1, 1, 1)) {}

	const glm::vec2& Vertex::getPosition() const {
		return position;
	}

	const glm::vec3& Vertex::getColour() const {
		return colour;
	}

	void Vertex::setPosition(glm::vec2 data) {
		position = data;
	}

	void Vertex::setColour(const glm::vec3& data) {
		colour = data;
	}

	void Vertex::multiply(float scalar) {
		setPosition(glm::vec2(position.x * scalar, position.y * scalar));
	}
}