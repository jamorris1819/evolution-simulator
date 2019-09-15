#include "terrainmanager.h"
#include <noise\FastNoise.h>

TerrainManager::TerrainManager(GLuint program)
{
	this->program = program;
}

// Generates the hexagon tiles for the terrain.
void TerrainManager::generate(int width, int height, int tileSize)
{
	this->width = width;
	this->height = height;
	this->tileSize = tileSize;

	for (int y = 0; y < height; y++) {
		std::vector<Hex*> row;
		for (int x = 0; x < width; x++)	{
			glm::vec2 position;

			position.x = tileSize * x * sqrt(3);
			if (y % 2 != 0) position.x += tileSize * sqrt(3) / 2; // Offset if an odd row
			position.y = tileSize * y * 2 * 0.75f;
			Hex* hex = new Hex(tileSize, position, program);

			row.push_back(hex);
		}
		tiles.push_back(row);
	}
}



void TerrainManager::render()
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			tiles[x][y]->render();
		}
	}
}

void TerrainManager::paintTerrain(int seed)
{
	FastNoise noise;
	noise.SetNoiseType(FastNoise::ValueFractal);
	noise.SetSeed(seed);
	noise.SetFractalOctaves(8);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Hex* hex = tiles[x][y];

			float z = noise.GetNoise(x, y) / 1.0f;

			glm::vec3 colour = glm::vec3(z, z, z) * 255.0f;

			if (z < 0.02f) colour = glm::vec3(67, 136, 178);
			else if (z < 0.1f) colour = glm::vec3(87, 156, 198);
			else if (z < 0.15f) colour = glm::vec3(206, 162, 125);
			else if (z < 0.2f) colour = glm::vec3(239, 205, 178);
			else if (z < 0.55f) colour = glm::vec3(137, 162, 61);
			else if (z < 0.7f) colour = glm::vec3(23, 97, 38);
			else if (z < 0.85f) colour = glm::vec3(134, 140, 136);
			else colour = glm::vec3(81, 88, 81);

			colour /= 255.0f;

			hex->enableOverrideColour(colour);
		}
	}
}
