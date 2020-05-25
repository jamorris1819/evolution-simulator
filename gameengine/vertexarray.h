#pragma once

#include <vector>
#include "vertex.h"

namespace engine {
	class VertexArray {
	public:
		VertexArray() { generate(); }
		
		VertexArray operator+ (const VertexArray& a);
		VertexArray& operator+= (const VertexArray& a) { *this = *this + a; return *this; }

		std::vector<Vertex> const& getVertices() const { return vertices; }
		void setVertices(std::vector<Vertex> const& data);

		std::vector<unsigned short> const& getIndices() const { return indices; }
		void setIndices(std::vector<unsigned short> const& data) { indices = data; }

		int getVertexCount() const { return vertices.size(); }
		int getIndexCount() const { return indices.size(); }

		void setColour(glm::vec3 const& colour) {
			for (int i = 0; i < vertices.size(); i++) {
				vertices[i].setColour(colour);
			}
		}

		// called by children for self-contained vertexarray generation.
		virtual void generate() {}


	protected:
		std::vector<unsigned short> indices;
		std::vector<Vertex> vertices;

		// generates inefficient, but simple indices.
		void virtual generateIndices() {
			indices.clear();
			for (unsigned short i = 0; i < vertices.size(); i++)
				indices.push_back(indices.size());
		}
	};
}