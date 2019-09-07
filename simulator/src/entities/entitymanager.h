#pragma once

#include <vector>
#include "../creature/creature.h"

class EntityManager {
public:
	EntityManager(GLuint shader, b2World* world);
	Creature* createCreature(Genome* genome, NeuralGenome* neuralGenome, glm::vec2 position);
	Creature* createRandomCreature(glm::vec2 position);
	Creature* getTestCreature() { return creatureList[0]; }
	Creature* createChildCreature(Creature* creatureA, Creature* creatureB, glm::vec2 position);
	void update(double deltaTime);
	void render();
private:
	std::vector <Creature*> creatureList;
	GLuint shader;
	b2World* world;
};