#pragma once
#include "shadermanager.h"
#include "entitymanager.h"
#include "noisegenerator.h"

namespace engine {
	class TerrainGenerator {
	public:
		TerrainGenerator(EntityManager& em, ShaderManager& sm, NoiseGenerator* ng) : entityManager(em),
			shaderManager(sm) {
			noise = ng;
		}
		void generate(int width, int height);
	private:
		EntityManager& entityManager;
		ShaderManager& shaderManager;
		NoiseGenerator* noise;
	};
}