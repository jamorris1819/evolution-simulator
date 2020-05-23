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

		// called by children for self-contained vertexarray generation.
		virtual void generate() {}

		void fromMany(std::vector<VertexArray> const & vertexArrays) {
			if (vertexArrays.size() == 0) {
				vertices.clear();
				indices.clear();
			}
			if (vertexArrays.size() == 1) {
				vertices = vertexArrays[0].vertices;
				indices = vertexArrays[0].indices;
			}

			int vertexCount = 0;
			int indexCount = 0;
			for (int i = 0; i < vertexArrays.size(); i++) {
				vertexCount += vertexArrays[i].getVertexCount();
				indexCount += vertexArrays[i].getIndexCount();
			}

			std::vector<Vertex> newVertices(vertexCount);
			std::vector<unsigned short> newIndices(indexCount);

			int vertexCumulative = 0;
			int indexCumulative = 0;
			unsigned short indexOffset = 0;
			for(int i = 0; i < vertexArrays.size(); i++) {
				VertexArray va = vertexArrays[i];
				for (int j = 0; j < va.getVertexCount(); j++) {
					newVertices[vertexCumulative++] = va.getVertices()[j];
				}

				for (int j = 0; j < va.getIndexCount(); j++) {
					newIndices[indexCumulative++] = va.getIndices()[j] + indexOffset;
				}

				indexOffset += va.getVertexCount();
			}

			vertices = newVertices;
			indices = newIndices;
		};

		

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