#include "bush.h"
#include "bushbody.h"

Bush::Bush(GLuint shader, b2World* world, glm::vec3 position) : Plant(shader, world, position)
{
	body = new BushBody(shader, world);
	availableFruit = 0;
	timeToReplenish = 4 + (rand() % 6);
	internalTimer = 0;
	maxFruit = 0;
}

void Bush::generate()
{
	Plant::generate();
	maxFruit = ((BushBody*)(PlantBody*)body)->fruit.size();
}

void Bush::beConsumed()
{
	availableFruit--;
	if (availableFruit < 0) availableFruit = 0;
	BushBody* bushBody = (BushBody*)(PlantBody*)body;
	bushBody->setVisibleFruit(availableFruit);
}

void Bush::update(double deltaTime)
{
	Plant::update(deltaTime);

	// If fruit is missing, replenish it.
	if(availableFruit < maxFruit) internalTimer += deltaTime;

	if (internalTimer > timeToReplenish) {
		internalTimer = 0;
		if (availableFruit < maxFruit) {
			// TODO: energy cost
			availableFruit++;
			BushBody* bushBody = (BushBody*)(PlantBody*)body;
			bushBody->setVisibleFruit(availableFruit);
		}
	}
}
