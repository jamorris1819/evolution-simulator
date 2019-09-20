#pragma once
#include "hex.h"
#include <noise\FastNoise.h>

class TerrainManager {
public:
	TerrainManager(GLuint program);
	void generate(int width, int height, int tileSize);
	void render();
	void paintTerrain();
	void update(double deltaTime);
	void updateNoiseHeightMap(int id, int seed, float scale, int noiseType, float frequency, int fractalType, int octaves, float lacunarity, float gain, int offsetX, int offsetY);
	void createNoiseHeightMap(int seed, float scale, int noiseType, float frequency, int fractalType, int octaves, float lacunarity, float gain, int offsetX, int offsetY);
	int noiseHeightMapCount();

private:
	std::vector<FastNoise*> noiseHeightMaps;
	GLuint program;
	int width;
	int height;
	int tileSize;
	int offsetX;
	int offsetY;
	std::vector<std::vector<Hex*>> tiles;
	FastNoise* createNoise(int seed, float scale, int noiseType, float frequency, int fractalType, int octaves, float lacunarity, float gain, int offsetX, int offsetY);
	void updateNoise(FastNoise* noise, int seed, float scale, int noiseType, float frequency, int fractalType, int octaves, float lacunarity, float gain, int offsetX, int offsetY);
};