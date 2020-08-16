#pragma once
#include "FastNoise.h"
#include "biometype.h"
#include <vector>

namespace engine {
	class NoiseGenerator {
	public:
		double generate(double x, double y);
		std::vector<BiomeType> generateHexagon(double x, double y, int size);
	};
}