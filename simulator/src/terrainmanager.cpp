#include "terrainmanager.h"

TerrainManager::TerrainManager(GLuint program)
{
	this->program = program;
	temperature = new FastNoise();
	temperature->SetNoiseType(FastNoise::NoiseType::Perlin);
	temperature->SetFrequency(0.1);
	temperature->SetSeed(rand());
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

int TerrainManager::createNoiseHeightMap()
{
	noiseHeightLayers.push_back(NoiseLayer());
	noiseHeightGenerators.push_back(new FastNoise());

	if (noiseHeightLayers.size() == 1) {
		noiseHeightLayers[0].enabled = true;
		noiseHeightLayers[0].inverse = false;
		noiseHeightLayers[0].seed = 0;
		noiseHeightLayers[0].scale = 1.0f;
		noiseHeightLayers[0].noiseType = 9;
		noiseHeightLayers[0].frequency = 0.1f;
		noiseHeightLayers[0].fractalType = 2;
		noiseHeightLayers[0].octaves = 3;
		noiseHeightLayers[0].lacunarity = 0.5f;
		noiseHeightLayers[0].gain = 0.5f;
		noiseHeightLayers[0].offsetX = 0;
		noiseHeightLayers[0].offsetY = 0;
	}

	return noiseHeightLayers.size() - 1;
}

void TerrainManager::deleteNoiseHeightMap(int id)
{
	noiseHeightGenerators.erase(noiseHeightGenerators.begin() + id);
	noiseHeightLayers.erase(noiseHeightLayers.begin() + id);
}

int TerrainManager::noiseHeightMapCount()
{
	return noiseHeightLayers.size();
}


NoiseLayer& TerrainManager::getNoiseLayer(int id)
{
	return noiseHeightLayers[id];
}

int TerrainManager::getWidth()
{
	return width;
}

int TerrainManager::getHeight()
{
	return height;
}

int TerrainManager::getTileSize()
{
	return tileSize;
}

void TerrainManager::updateNoiseLayer(int id, string name, bool enabled, bool inverse, int seed, float scale, int noiseType, float frequency, int fractalType, int octaves, float lacunarity, float gain, int offsetX, int offsetY)
{
	if (id > noiseHeightLayers.size() - 1) return;

	noiseHeightLayers[id].name = string(name.c_str());
	noiseHeightLayers[id].enabled = enabled;
	noiseHeightLayers[id].inverse = inverse;
	noiseHeightLayers[id].seed = seed;
	noiseHeightLayers[id].scale = scale;
	noiseHeightLayers[id].noiseType = noiseType;
	noiseHeightLayers[id].frequency = frequency;
	noiseHeightLayers[id].fractalType = fractalType;
	noiseHeightLayers[id].octaves = octaves;
	noiseHeightLayers[id].lacunarity = lacunarity;
	noiseHeightLayers[id].gain = gain;
	noiseHeightLayers[id].offsetX = offsetX;
	noiseHeightLayers[id].offsetY = offsetY;

	updateNoise(noiseHeightGenerators[id], noiseHeightLayers[id]);
}

void TerrainManager::updateNoise(FastNoise* noise, NoiseLayer layer)
{
	updateNoise(noise, layer.name, layer.seed, layer.scale, layer.noiseType, layer.frequency, layer.fractalType, layer.octaves, layer.lacunarity, layer.gain, layer.offsetX, layer.offsetY);
}

void TerrainManager::updateNoise(FastNoise* noise, string name, int seed, float scale, int noiseType, float frequency, int fractalType, int octaves, float lacunarity, float gain, int offsetX, int offsetY)
{
	noise->SetNoiseType((FastNoise::NoiseType)noiseType);
	noise->SetFrequency(frequency);
	noise->SetSeed(seed);
	noise->SetFractalType((FastNoise::FractalType)fractalType);
	noise->SetFractalOctaves(octaves);
	noise->SetFractalLacunarity(lacunarity);
	noise->SetFractalGain(gain);
}

float TerrainManager::getHeightNoise(float x, float y)
{
	float z = 0.0f;
	for (int i = 0; i < noiseHeightLayers.size(); i++) {
		if (!noiseHeightLayers[i].enabled) continue;

		float noise = noiseHeightGenerators[i]->GetNoise(x + noiseHeightLayers[i].offsetY, y + noiseHeightLayers[i].offsetX);
		noise *= noiseHeightLayers[i].inverse ? -1.0f : 1.0f;
		noise *= noiseHeightLayers[i].scale;
		z += noise;
	}
	return z;
}

float TerrainManager::getTemperature(float x, float y)
{
	float out = 0.0f;
	if (y < height / 2.0f) {
		out = y / (height * 0.5f);
	}
	else {
		out = 1.0f - ((y - (height * 0.5f)) / (height * 0.5f));
	}

	return out + temperature->GetNoise(x, y) * 0.25f;
}

void TerrainManager::paintTerrain()
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			Hex* hex = tiles[x][y];

			float z = getHeightNoise(x, y);


			glm::vec3 colour = glm::vec3(z, z, z) * 255.0f;

			// Height colours

			

			float temp = getTemperature(y, x);

			hex->setFade(z < 0.15f && temp > 0.3f); // fade the ocean

			if (z < 0.15f && noiseHeightLayers.size() > 0) {
				//hex->setFadeOffset(noiseHeightMaps[0]->GetNoise(x, y) * 10);
			}

			if (temp > 0.3f) {
				if (z < 0.02f) colour = glm::vec3(6, 66, 115); // dark blue
				else if (z < 0.1f) colour = glm::vec3(29, 162, 216); // light blue
				else if (z < 0.2f) colour = glm::vec3(219, 202, 105); // sand
				else if (z < 0.55f) {

					if (temp > 0.7f) colour = glm::vec3(219, 202, 105); // desert
					else if (temp > 0.3f) colour = glm::vec3(102, 141, 60); // grassland
					else colour = glm::vec3(238, 238, 238); // snow
				}
				else colour = glm::vec3(73, 56, 41); 
			}
			else {
				if (z < 0.2f) colour = glm::vec3(71, 123, 195); // ice
				else  colour = glm::vec3(238, 238, 238); // snow
			}

			int shade = rand() % 10;
			if (z >= 0.15f) colour += glm::vec3(shade, shade, shade);

			colour /= 255.0f;

			hex->enableOverrideColour(colour);
		}
	}
}

void TerrainManager::update(double deltaTime)
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			tiles[x][y]->update(deltaTime);
		}
	}
}


/*if (z < 0.02f) colour = glm::vec3(6, 66, 115); // dark blue
else if (z < 0.1f) colour = glm::vec3(29, 162, 216); // light blue
else if (z < 0.2f) colour = glm::vec3(219, 202, 105); // sand
else if (z < 0.55f) colour = glm::vec3(102, 141, 60); // grass
else if (z < 0.7f) colour = glm::vec3(23, 97, 38); // forest
else if (z < 0.85f) colour = glm::vec3(134, 140, 136); // mountain
else colour = glm::vec3(81, 88, 81); // high mountain*/