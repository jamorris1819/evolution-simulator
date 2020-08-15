#include "pch.h"
#include "worldtile.h"

namespace engine {
	void WorldTile::generate() {
		std::vector<engine::Vertex> vertices;
		std::vector<unsigned short> indices;

		// As vertices will contain barycentric coordinates, we cannot re-use them.
		for (int i = 0; i < 6; i++) {
			// first point
			float angle_deg = 60 * i - 30;
			float angle_rad = PI / 180 * angle_deg;
			engine::Vertex v1(cos(angle_rad) * size, sin(angle_rad) * size);
			v1.setBarycentricCoordinate(glm::vec3(1, 0, 0));

			// second point
			angle_deg = 60 * (i + 1) - 30;
			angle_rad = PI / 180 * angle_deg;
			engine::Vertex v2(cos(angle_rad) * size, sin(angle_rad) * size);
			v2.setBarycentricCoordinate(glm::vec3(0, 1, 0));

			// origin point
			engine::Vertex origin(0, 0);
			origin.setBarycentricCoordinate(glm::vec3(0, 0, 1));

			glm::vec3 p1Col = BiomeColour::get(biomes[i + 1]);
			glm::vec3 p2Col = BiomeColour::get(biomes[i + 2 == 7 ? 1 : i + 2]); // get the next biome. unless we need to loop... then loop
			glm::vec3 oCol = BiomeColour::get(biomes[0]);

			// assign the colours to the vertices
			v1.setColour(0, p1Col);
			v1.setColour(1, p2Col);
			v1.setColour(2, oCol);

			v2.setColour(0, p1Col);
			v2.setColour(1, p2Col);
			v2.setColour(2, oCol);

			origin.setColour(0, p1Col);
			origin.setColour(1, p2Col);
			origin.setColour(2, oCol);

			// push the vertices into the shape
			vertices.push_back(v1);
			indices.push_back(indices.size());
			vertices.push_back(v2);
			indices.push_back(indices.size());
			vertices.push_back(origin);
			indices.push_back(indices.size());
		}

		setVertices(vertices);
		setIndices(indices);
	}
}