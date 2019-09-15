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

void TerrainManager::paintTerrain(int seed, float scale, int noiseType, float frequency, int fractalType, int octaves, float lacunarity, float gain, int offsetX, int offsetY)
{
	FastNoise noiseHeight;
	noiseHeight.SetNoiseType((FastNoise::NoiseType)noiseType); 
	noiseHeight.SetSeed(seed);
	noiseHeight.SetFrequency(frequency);

	noiseHeight.SetFractalType((FastNoise::FractalType)fractalType);
	noiseHeight.SetFractalOctaves(octaves);
	noiseHeight.SetFractalLacunarity(lacunarity);
	noiseHeight.SetFractalGain(gain);

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Hex* hex = tiles[x][y];

			float z = noiseHeight.GetNoise(x + offsetY, y + offsetX) * scale;


			glm::vec3 colour = glm::vec3(z, z, z) * 255.0f;

			// Height colours

			if (z < 0.02f) colour = glm::vec3(67, 136, 178); // dark blue
			else if (z < 0.1f) colour = glm::vec3(87, 156, 198); // light blue
			else if (z < 0.15f) colour = glm::vec3(206, 162, 125); // wet sand
			else if (z < 0.2f) colour = glm::vec3(239, 205, 178); // dry sand
			else if (z < 0.55f) colour = glm::vec3(137, 162, 61); // grass
			else if (z < 0.7f) colour = glm::vec3(23, 97, 38); // forest
			else if (z < 0.85f) colour = glm::vec3(134, 140, 136); // mountain
			else colour = glm::vec3(81, 88, 81); // high mountain

			colour /= 255.0f;

			hex->enableOverrideColour(colour);
		}
	}
}
