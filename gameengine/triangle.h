#pragma once
#include "vertexarray.h"

namespace engine {
	class Triangle : public VertexArray {
	public:
		Triangle(int w, int h) : VertexArray(), width(w), height(h) {
			vertices = {
				glm::vec2(0, h * 0.5),
				glm::vec2(-w * 0.5, -h * 0.5),
				glm::vec2(w * 0.5, -h * 0.5),
			};
			indices = {
				0, 1, 2
			};
			vertices[0].setColour(glm::vec3(1, 0, 0));
			vertices[1].setColour(glm::vec3(0, 1, 0));
			vertices[2].setColour(glm::vec3(0, 0, 1));

			vertices[0].setBarycentricCoordinate(glm::vec3(1, 0, 0));
			vertices[1].setBarycentricCoordinate(glm::vec3(0, 1, 0));
			vertices[2].setBarycentricCoordinate(glm::vec3(0, 0, 1));
		}
		int width;
		int height;
	};
}