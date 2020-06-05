#pragma once
#include "vertexarray.h"

namespace engine {
	class Rectangle : public VertexArray {
	public:
		Rectangle(int w, int h) : VertexArray(), width(w), height(h) {
			vertices = {
				glm::vec2(-w * 0.5, h * 0.5),
				glm::vec2(-w * 0.5, -h * 0.5),
				glm::vec2(w * 0.5, -h * 0.5),
				glm::vec2(w * 0.5, h * 0.5)
			};
			indices = {
				0, 1, 2, 2, 3, 0
			};
		}
		int width;
		int height;
	};
}