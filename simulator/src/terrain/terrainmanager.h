#pragma once
#include "hex.h"
#include "noiselayer.h"
#include <noise\FastNoise.h>

class TerrainManager {
public:
	TerrainManager(GLuint program);
	void generate(int width, int height, int tileSize);
	void render();
	void paintTerrain();
	void update(double deltaTime);
	int createNoiseHeightMap();
	void deleteNoiseHeightMap(int id);
	float getHeightNoise(float x, float y);
	float getTemperature(float x, float y);
	int noiseHeightMapCount();
	void updateNoiseLayer(int id, string name, bool enabled, bool inverse, int seed, float scale, int noiseType, float frequency, int fractalType, int octaves, float lacunarity, float gain, int offsetX, int offsetY);
	NoiseLayer& getNoiseLayer(int id);
	int getWidth();
	int getHeight();
	int getTileSize();

private:
	std::vector<NoiseLayer> noiseHeightLayers;
	std::vector<FastNoise*> noiseHeightGenerators;
	FastNoise* temperature;
	GLuint program;
	int width;
	int height;
	int tileSize;
	int offsetX;
	int offsetY;
	std::vector<std::vector<Hex*>> tiles;
	void updateNoise(FastNoise* noise, NoiseLayer layer);
	void updateNoise(FastNoise* noise, string name, int seed, float scale, int noiseType, float frequency, int fractalType, int octaves, float lacunarity, float gain, int offsetX, int offsetY);
};