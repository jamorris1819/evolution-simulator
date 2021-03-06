#include "entitymanager.h"
#include "bush.h"

EntityManager::EntityManager(GLuint shader, TerrainManager* terrainManager) {
	this->shader = shader;
	this->terrainManager = terrainManager;
}

/*void EntityManager::createPlant(glm::vec2 position) {
	Plant* plant = new Bush(shader, glm::vec3(position, 0));
	Genome* genome = new Genome(false);
	genome->generatePlant();
	plant->setGenome(genome);
	plant->generate();

	entityList.push_back(plant);
}*/

Creature* EntityManager::createCreature(Genome* genome, NeuralGenome* neuralGenome, glm::vec2 position) {
	Creature* newCreature = new Creature(this->shader, position);
	newCreature->setGenome(genome);
	newCreature->setNeuralGenome(neuralGenome);
	newCreature->canReproduce = true;
	newCreature->generate();
	//newCreature->body->setRotation((rand() % 360) * 3.141582653f / 180);
	entityList.push_back(newCreature);

	return newCreature;
}

Creature* EntityManager::createCreatureQueue(Genome* genome, NeuralGenome* neuralGenome, glm::vec2 position) {
	Creature* newCreature = new Creature(this->shader, position);
	newCreature->setGenome(genome);
	newCreature->setNeuralGenome(neuralGenome);
	generationQueue.push(newCreature);

	return newCreature;
}

Creature* EntityManager::createRandomCreature(glm::vec2 position) {
	Genome* genome = new Genome(true);
	genome->generateCreature();
	NeuralGenome* neuralGenome = new NeuralGenome(4, 1);

	for (int i = 0; i < 5; i++) {
		neuralGenome->mutateAddConnection();
	}

	return createCreature(genome, neuralGenome, position);
}

Creature* EntityManager::createChildCreature(Creature* creatureA, Creature* creatureB, glm::vec2 position) {
	Genome* childGenome = Genome::cross(creatureA->getGenome(), creatureB->getGenome());
	NeuralGenome* childNeuralGenome = NeuralGenome::cross(creatureA->getNeuralGenome(), creatureB->getNeuralGenome());

	for (int i = 0; i < 3; i++) {
		childGenome->mutate();
		childNeuralGenome->mutateAddConnection();
	}

	return createCreature(childGenome, childNeuralGenome, position);
}

Creature* EntityManager::createChildCreatureQueue(Creature* creatureA, Creature* creatureB, glm::vec2 position) {
	Genome* childGenome = Genome::cross(creatureA->getGenome(), creatureB->getGenome());
	NeuralGenome* childNeuralGenome = NeuralGenome::cross(creatureA->getNeuralGenome(), creatureB->getNeuralGenome());

	for (int i = 0; i < 3; i++) {
		childGenome->mutate();
		childNeuralGenome->mutateAddConnection();
	}

	return createCreatureQueue(childGenome, childNeuralGenome, position);
}

void EntityManager::update(double deltaTime) {
	//if (!world->IsLocked()) {
		while (!generationQueue.empty()) {
			Creature* creature = generationQueue.front();
			generationQueue.pop();
			creature->generate();
			entityList.push_back(creature);
		}
	//}

	for (int i = 0; i < entityList.size(); i++) {
		entityList[i]->update(deltaTime, entityList);
		int tileSize = terrainManager->getTileSize();
		int x = entityList[i]->getPosition().x;
		int y = entityList[i]->getPosition().y;

		entityList[i]->setInWater(terrainManager->getHeightNoise(x / tileSize, y / tileSize) < 0.15f);
	}
}

void EntityManager::render() {
	for (int i = 0; i < entityList.size(); i++) {
		entityList[i]->render();
	}
}