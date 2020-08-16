#include "pch.h"
#include "terraingenerator.h"
#include "biometype.h"
#include "worldtile.h"
#include "rendercomponent.h"
#include "positioncomponent.h"
#include "shadermanager.h"

void TerrainGenerator::generate(int width, int height) {
	int tileSize = 4;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			engine::Entity* e = new engine::Entity("test");

			BiomeType biomes[7] = {};
			auto b = noise->generateHexagon(x, y, 4);
			for (int i = 0; i < 7; i++)
				biomes[i] = b[i];

			auto tile = WorldTile(biomes);
			tile.generate();

			auto rc = new engine::RenderComponent(tile);
				
			rc->shaders.push_back(shaderManager.getShader("basic"));
			e->addComponent(rc);

			double posX = tileSize * x * sqrt(3);
			if (y % 2 != 0) posX += tileSize * sqrt(3) / 2; // Offset if an odd row
			double posY = tileSize * y * 2 * 0.75f;

			e->addComponent(new engine::PositionComponent(glm::vec2(posX, posY)));
			entityManager.addEntity(e);
		}
	}
}