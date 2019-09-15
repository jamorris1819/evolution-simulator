#pragma once
#include "hex.h"

class TerrainManager {
public:
	TerrainManager(GLuint program);
	void generate(int width, int height, int tileSize);
	void render();
	void paintTerrain(int seed);
private:
	GLuint program;
	int width;
	int height;
	int tileSize;
	std::vector<std::vector<Hex*>> tiles;
};