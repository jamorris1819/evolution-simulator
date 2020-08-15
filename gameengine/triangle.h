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

			for (int i = 0; i < 2; i++) {
				vertices[i].setColour(0, glm::vec3(0, 0, 1));
				vertices[i].setColour(1, glm::vec3(0, 1, 0));
				vertices[i].setColour(2, glm::vec3(0, 0, 1));
			}


			vertices[2].setColour(0, glm::vec3(1, 1, 1));
			vertices[2].setColour(1, glm::vec3(1, 1, 0));
			vertices[2].setColour(2, glm::vec3(0, 1, 1));

			vertices[0].setBarycentricCoordinate(glm::vec3(1, 0, 0));
			vertices[1].setBarycentricCoordinate(glm::vec3(0, 1, 0));
			vertices[2].setBarycentricCoordinate(glm::vec3(0, 0, 1));
		}
		Triangle() : VertexArray(), width(0), height(0) {}
		Triangle(Vertex v1, Vertex v2, Vertex v3) : VertexArray(), width(0), height(0) {
			vertices = { v1, v2, v3 };
			indices = { 0, 1, 2 };

			vertices[0].setBarycentricCoordinate(glm::vec3(1, 0, 0));
			vertices[1].setBarycentricCoordinate(glm::vec3(0, 1, 0));
			vertices[2].setBarycentricCoordinate(glm::vec3(0, 0, 1));
		}
		int width;
		int height;
	};
}