#pragma once

#include <vector>
#include "triangle.h"

namespace eng {
	class VertexArray {
	public:
		VertexArray() { generate(); }

		std::vector<Vertex> const& getVertices() const { return vertices; }
		void setVertices(std::vector<Vertex> const& data) {
			vertices = data;
			generateIndices();
		}

		std::vector<unsigned short> const& getIndices() const { return indices; }
		void setIndices(std::vector<unsigned short> const& data) { indices = data; }

		int getVertexCount() const { return vertices.size(); }
		int getIndexCount() const { return indices.size(); }

		void setColour(glm::vec3 const& colour) {
			for (int i = 0; i < vertices.size(); i++) {
				vertices[i].setColour(colour);
			}
		}

		// generates inefficient, but simple indices.
		void generateIndices() {
			indices.clear();
			for (unsigned short i = 0; i < vertices.size(); i++)
				indices.push_back(indices.size());
		}

		// called by children for self-contained vertexarray generation.
		virtual void generate() {}

	protected:
		std::vector<unsigned short> indices;
		std::vector<Vertex> vertices;
	};
}