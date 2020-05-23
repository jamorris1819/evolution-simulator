#pragma once
#include "vertexarray.h"

namespace eng {
	class Polygon : public VertexArray {
	public:
		Polygon() : VertexArray() {}
	protected:
		/// <summary>
		/// Generate indices which turn the polygon data into triangles.
		/// </summary>
		virtual void generateIndices() override {
			if (getVertexCount() == 0) return;
			//if (!hasOriginVertex()) insertOriginVertex();

			indices.clear();

			for (int i = 1; i < getVertexCount(); ++i) {
				indices.push_back(i);
				indices.push_back(0);
				indices.push_back(i + 1 < getVertexCount() ? i + 1 : 1); // loop back to start
			}
		}

	private:
		bool hasOriginVertex() { return vertices[0].getPosition() == glm::vec2(0, 0); }
		void insertOriginVertex() {
			Vertex origin;
			origin.setPosition(glm::vec2(0, 0));
			origin.setColour(vertices[0].getColour());
			vertices.insert(vertices.begin(), origin);
		}
	};
}