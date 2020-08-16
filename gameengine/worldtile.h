#pragma once
#include "hexagon.h"
#include "biometype.h"

namespace engine {
	class WorldTile : public Hexagon {
	public:
		// first biome is centre, the rest go anti clockwise from bottom right
		WorldTile(BiomeType b[7]) : Hexagon(4), biomes() {
			for (int i = 0; i < 7; i++)
				biomes[i] = b[i];
		}
		WorldTile() : Hexagon(4), biomes() {
			for (int i = 0; i < 7; i++)
				biomes[i] = BiomeType::WATER;
		}
		virtual void generate() override;
	private:
		BiomeType biomes[7];
	};
}