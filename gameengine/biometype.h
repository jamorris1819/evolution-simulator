#pragma once
#include "glm/vec3.hpp"

enum class BiomeType : unsigned {
	WATER = 0x0,
	DEEP_WATER = 0x1,
	GRASS = 0x2,
	TEST = 0x3
};

class BiomeColour {
public:
	static glm::vec3 get(BiomeType t) {
		switch (t) {
		case BiomeType::WATER: return glm::vec3(0.02, 0.259, 0.45);
		case BiomeType::DEEP_WATER: return glm::vec3(0.11, 0.63, 0.85);
		case BiomeType::GRASS: return glm::vec3(0.4, 0.553, 0.235);
		case BiomeType::TEST: return glm::vec3(0.5, 0.5, 1);
		}
	}
};