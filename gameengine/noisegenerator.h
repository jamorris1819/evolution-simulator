#pragma once
#include "FastNoise.h"
#include "biometype.h"
#include <memory>
#include <vector>

class NoiseGenerator {
public:
	NoiseGenerator(FastNoise* n) : noise(n) {}
	double generate(double x, double y);
	std::vector<BiomeType> generateHexagon(double x, double y, int size);
private:
	std::unique_ptr<FastNoise> noise;
	BiomeType getBiomeType(double height);
};