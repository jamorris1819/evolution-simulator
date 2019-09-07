#pragma once

#include <vector>
#include "../creature/creature.h"

class EntityManager {
public:
	EntityManager(GLuint shader, b2World* world);
	Creature* createCreature(glm::vec2 position);
	Creature* getTestCreature() { return creatureList[0]; }
	void update(double deltaTime);
	void render();
private:
	std::vector <Creature*> creatureList;
	GLuint shader;
	b2World* world;
};