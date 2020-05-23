#include "bush.h"
#include "bushbody.h"
/*
Bush::Bush(GLuint shader, b2World* world, glm::vec3 position) : Plant(shader, world, position) {
	//body = new BushBody(shader, world);
	availableFruit = 0;
	timeToReplenish = 4 + (double)(rand() % 6);
	internalTimer = 0;
	maxFruit = 0;
}

void Bush::generate() {
	/*Plant::generate();
	maxFruit = ((BushBody*)(PlantBody*)body)->fruit.size();
	availableFruit = maxFruit / 2;
	BushBody* bushBody = (BushBody*)(PlantBody*)body;
	bushBody->setVisibleFruit(availableFruit);
}

double Bush::beConsumed() {
	/*availableFruit--;
	if (availableFruit < 0) availableFruit = 0;
	BushBody* bushBody = (BushBody*)(PlantBody*)body;
	bushBody->setVisibleFruit(availableFruit);

	return 25;
}

void Bush::update(double deltaTime, std::vector<LivingEntity*>& entityList) {
	Plant::update(deltaTime, entityList);

	// If fruit is missing, replenish it.
	if (availableFruit < maxFruit) internalTimer += deltaTime;

	if (internalTimer > timeToReplenish) {
		internalTimer = 0;
		if (availableFruit < maxFruit) {
			// TODO: energy cost
			availableFruit++;
			//BushBody* bushBody = (BushBody*)(PlantBody*)body;
			//bushBody->setVisibleFruit(availableFruit);
		}
	}
}*/