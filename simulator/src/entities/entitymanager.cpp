#include "entitymanager.h"

EntityManager::EntityManager(GLuint shader, b2World* world)
{
	this->shader = shader;
	this->world = world;
}

Creature* EntityManager::createCreature(glm::vec2 position)
{
	Creature* newCreature = new Creature(shader, world, position);
	Genome* genome = new Genome(true);
	NeuralGenome* neuralGenome = new NeuralGenome(5, 3);

	for (int i = 0; i < 5; i++) {
		neuralGenome->mutateAddConnection();
	}

	newCreature->setGenome(genome);
	newCreature->setNeuralGenome(neuralGenome);
	newCreature->generate();
	creatureList.push_back(newCreature);

	return newCreature;
}

void EntityManager::update(double deltaTime)
{
	for (int i = 0; i < creatureList.size(); i++) {
		creatureList[i]->update(deltaTime);
	}
}

void EntityManager::render()
{
	for (int i = 0; i < creatureList.size(); i++) {
		creatureList[i]->render();
	}
}
