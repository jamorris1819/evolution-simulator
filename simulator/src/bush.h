#pragma once
#include "plant.h"

class Bush : public Plant {
public:
	Bush(GLuint shader, b2World* world, glm::vec3 position);
	double beConsumed() override;
	void update(double deltaTime) override;
	void generate() override;
private:
	int availableFruit;
	int maxFruit;
	double internalTimer;
	double timeToReplenish;
};