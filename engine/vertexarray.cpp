#include "pch.h"
#include "vertexarray.h"

namespace eng {
	VertexArray::VertexArray() {
	}

	void VertexArray::setVertices(std::vector<Vertex> const& data) {
		vertices = data;

		generateFloatData();
	}

	void VertexArray::setColour(glm::vec3 const& colour)
}