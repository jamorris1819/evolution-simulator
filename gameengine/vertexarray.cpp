#include "pch.h"
#include "vertexarray.h"

namespace engine {
	VertexArray VertexArray::operator+(const VertexArray& a) {
		int newVertexCount = getVertexCount() + a.getVertexCount();
		int newIndexCount = getIndexCount() + a.getIndexCount();

		std::vector<Vertex> newVertices(newVertexCount);
		std::vector<unsigned short> newIndices(newIndexCount);

		int vertexCumulative = 0;
		int indexCumulative = 0;

		// Copy our data in.
		for (int i = 0; i < getVertexCount(); i++) {
			newVertices[vertexCumulative++] = getVertices()[i];
		}
		for (int i = 0; i < getIndexCount(); i++) {
			newIndices[indexCumulative++] = getIndices()[i];
		}

		// Copy their data in.
		for (int i = 0; i < a.getVertexCount(); i++) {
			newVertices[vertexCumulative++] = a.getVertices()[i];
		}
		for (int i = 0; i < a.getIndexCount(); i++) {
			newIndices[indexCumulative++] = a.getIndices()[i] + getVertexCount();
		}

		VertexArray va;
		va.setVertices(newVertices);
		va.setIndices(newIndices);

		return va;
	}

	void VertexArray::setVertices(std::vector<Vertex> const& data) {
		vertices = data;
		generateIndices();
	}
}