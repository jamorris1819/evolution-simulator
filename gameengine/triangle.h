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
		}
		int width;
		int height;
	};
}