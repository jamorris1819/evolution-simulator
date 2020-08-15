#pragma once
#include "vertexarray.h"
#define PI 3.14159265359

namespace engine {
	class Hexagon : public VertexArray {
	public:
		Hexagon(int size) : VertexArray() {
			this->size = size;
		}
		void virtual generate() {
			engine::Vertex origin(0, 0);
			origin.setColour(glm::vec3(1, 0, 0));
			std::vector<engine::Vertex> vertices;

			vertices.push_back(origin);

			for (int i = 0; i < 6; i++) {
				float angle_deg = 60 * i - 30;
				float angle_rad = PI / 180 * angle_deg;
				engine::Vertex v(cos(angle_rad) * size, sin(angle_rad) * size);
				v.setColour(glm::vec3(v.getPosition(), 1)); //v.setColour(glm::vec3(1, 0, 0));
				vertices.push_back(v);
			}

			std::vector<unsigned short> indices{
				1, 0, 2, 2, 0, 3, 3, 0, 4, 4, 0, 5, 5, 0, 6, 6, 0, 1
			};

			setVertices(vertices);
			setIndices(indices);
		}
		int size;
	};
}