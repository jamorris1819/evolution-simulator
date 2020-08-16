#pragma once
#include "shadermanager.h"
#include "entitymanager.h"
#include "noisegenerator.h"

class TerrainGenerator {
public:
	TerrainGenerator(engine::EntityManager& em, engine::ShaderManager& sm, NoiseGenerator* ng) : entityManager(em),
		shaderManager(sm) {
		noise = ng;
	}
	void generate(int width, int height);
private:
	engine::EntityManager& entityManager;
	engine::ShaderManager& shaderManager;
	NoiseGenerator* noise;
};