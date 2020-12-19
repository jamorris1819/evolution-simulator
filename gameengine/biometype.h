#pragma once
#include "glm/vec3.hpp"

enum class BiomeType : unsigned {
	WATER = 0x0,
	DEEP_WATER = 0x1,
	BEACH = 0x2,
	GRASS = 0x3,
	TEST = 0x4
};

class BiomeColour {
public:
	static glm::vec3 get(BiomeType t) {
		switch (t) {
		case BiomeType::WATER: return glm::vec3(0.02, 0.259, 0.45);
		case BiomeType::DEEP_WATER: return glm::vec3(0.01, 0.159, 0.3);
		case BiomeType::BEACH: return glm::vec3(0.95, 0.82, 0.42);
		case BiomeType::GRASS: return glm::vec3(0.4, 0.553, 0.235);
		case BiomeType::TEST: return glm::vec3(0.56, 0.42, 0.25);
		}
	}
};