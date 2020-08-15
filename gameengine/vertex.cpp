#include "pch.h"
#include "vertex.h"

namespace engine {
	Vertex::Vertex() : position(glm::vec2(0, 0)), colours(), barycentricCoordinate(glm::vec3(0, 0, 0)) {}

	Vertex::Vertex(glm::vec2 pos) : position(pos), colours(), barycentricCoordinate(glm::vec3(0, 0, 0)) {}

	Vertex::Vertex(float x, float y) : position(glm::vec2(x, y)), colours(), barycentricCoordinate(glm::vec3(0, 0, 0)) {}

	const glm::vec2& Vertex::getPosition() const {
		return position;
	}

	const glm::vec3& Vertex::getColour() const {
		return colours[0];
	}

	const glm::vec3& Vertex::getColour(int index) const {
		if (index < 0 || index > 3) return glm::vec3(1, 0, 1);

		return colours[index];
	}

	const glm::vec3& Vertex::getBarycentricCoordinate() const {
		return barycentricCoordinate;
	}

	void Vertex::setPosition(glm::vec2 data) {
		position = data;
	}

	void Vertex::setColour(const glm::vec3& data) {
		colours[0] = data;
	}

	void Vertex::setColour(int index, const glm::vec3& data) {
		if (index < 0 || index > 3) return;

		colours[index] = data;
	}

	void Vertex::setBarycentricCoordinate(const glm::vec3& data) {
		barycentricCoordinate = data;
	}

	void Vertex::multiply(float scalar) {
		setPosition(glm::vec2(position.x * scalar, position.y * scalar));
	}
}