#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <vector>

namespace engine {
	class Vertex {
	public:
		Vertex();
		Vertex(float x, float y);
		Vertex(glm::vec2 pos);
		const glm::vec2& getPosition() const;
		const glm::vec3& getColour() const;
		const glm::vec3& getColour(int index) const;
		const glm::vec3& getBarycentricCoordinate() const;
		void setPosition(glm::vec2 data);
		void setColour(const glm::vec3& data);
		void setColour(int index, const glm::vec3& data);
		void setBarycentricCoordinate(const glm::vec3& data);
		void multiply(float scalar);

	private:
		glm::vec2 position;
		glm::vec3 colours[3];
		glm::vec3 barycentricCoordinate;
	};
}