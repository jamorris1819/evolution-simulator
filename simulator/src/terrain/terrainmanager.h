#pragma once
#include "hex.h"

class TerrainManager {
public:
	TerrainManager(GLuint program);
	void generate(int width, int height, int tileSize);
	void render();
	void paintTerrain(int seed, float scale, int noiseType, float frequency, int fractalType, int octaves, float lacunarity, float gain, int offsetX, int offsetY);
private:
	GLuint program;
	int width;
	int height;
	int tileSize;
	std::vector<std::vector<Hex*>> tiles;
};