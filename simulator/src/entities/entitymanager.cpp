#include "entitymanager.h"

EntityManager::EntityManager(GLuint shader, b2World* world)
{
	this->shader = shader;
	this->world = world;
}

Creature* EntityManager::createCreature(Genome* genome, NeuralGenome* neuralGenome, glm::vec2 position)
{
	Creature* newCreature = new Creature(shader, world, position);
	newCreature->setGenome(genome);
	newCreature->setNeuralGenome(neuralGenome);
	newCreature->generate();
	creatureList.push_back(newCreature);

	return newCreature;
}

Creature* EntityManager::createRandomCreature(glm::vec2 position)
{
	Genome* genome = new Genome(true);
	NeuralGenome* neuralGenome = new NeuralGenome(5, 3);

	for (int i = 0; i < 5; i++) {
		neuralGenome->mutateAddConnection();
	}

	return createCreature(genome, neuralGenome, position);
}

Creature* EntityManager::createChildCreature(Creature* creatureA, Creature* creatureB, glm::vec2 position)
{
	Genome* childGenome = Genome::cross(creatureA->getGenome(), creatureB->getGenome());
	NeuralGenome* childNeuralGenome = NeuralGenome::cross(creatureA->getNeuralGenome(), creatureB->getNeuralGenome());

	for (int i = 0; i < 3; i++) {
		childGenome->mutate();
		childNeuralGenome->mutateAddConnection();
	}

	return createCreature(childGenome, childNeuralGenome, position);
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
