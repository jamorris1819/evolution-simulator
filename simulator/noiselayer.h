#pragma once

struct NoiseLayer {
	std::string name;
	bool enabled;
	bool inverse;
	int seed;
	float scale;
	int noiseType;
	float frequency;
	int fractalType;
	int octaves;
	float lacunarity;
	float gain;
	int offsetX;
	int offsetY;
};