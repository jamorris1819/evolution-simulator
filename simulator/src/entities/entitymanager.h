#pragma once

#include <vector>
#include <queue>
#include <glm/vec3.hpp>
#include "../creature/creature.h"

class EntityManager {
public:
	EntityManager(GLuint shader, b2World* world);
	Creature* createCreature(Genome* genome, NeuralGenome* neuralGenome, glm::vec2 position);
	Creature* createCreatureQueue(Genome* genome, NeuralGenome* neuralGenome, glm::vec2 position);
	Creature* createRandomCreature(glm::vec2 position);
	Creature* getTestCreature() { return creatureList.size() > 0 ? creatureList[0] : nullptr; }
	Creature* createChildCreature(Creature* creatureA, Creature* creatureB, glm::vec2 position);
	Creature* createChildCreatureQueue(Creature* creatureA, Creature* creatureB, glm::vec2 position);
	void update(double deltaTime);
	void render();
private:
	std::vector <Creature*> creatureList;
	std::queue<Creature*> generationQueue;
	GLuint shader;
	b2World* world;
};