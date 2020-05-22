#pragma once

#include <vector>
#include <queue>
#include <glm/vec3.hpp>
#include "creature.h"
#include "plant.h"
#include "terrainmanager.h"

class EntityManager {
public:
	EntityManager(GLuint shader, b2World* world, TerrainManager* terrainManager);
	void createPlant(glm::vec2 position);
	Creature* createCreature(Genome* genome, NeuralGenome* neuralGenome, glm::vec2 position);
	Creature* createCreatureQueue(Genome* genome, NeuralGenome* neuralGenome, glm::vec2 position);
	Creature* createRandomCreature(glm::vec2 position);
	LivingEntity* getTestCreature() { return entityList.size() > 0 ? entityList[0] : nullptr; }
	Creature* createChildCreature(Creature* creatureA, Creature* creatureB, glm::vec2 position);
	Creature* createChildCreatureQueue(Creature* creatureA, Creature* creatureB, glm::vec2 position);
	void update(double deltaTime);
	void render();
private:
	std::vector <LivingEntity*> entityList;
	std::queue<Creature*> generationQueue;
	GLuint shader;
	b2World* world;
	TerrainManager* terrainManager;
};