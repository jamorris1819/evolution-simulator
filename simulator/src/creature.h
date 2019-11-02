#pragma once
#include "body.h"
#include "genome.h"
#include "livingentity.h"
#include "glm\vec2.hpp"
#include "neuralgenome.h"
#include "plant.h"

class Creature : public LivingEntity
{
public:
	Creature(GLuint shader, b2World* world, glm::vec2 position);
	~Creature();
	void setNeuralGenome(NeuralGenome* neuralGenome);
	NeuralGenome* getNeuralGenome();
	virtual void generate();
	void update(double deltaTime, std::vector<Creature*>& creatureList, std::vector<Plant*>& plantList);
	void moveForward(double power);
	bool canReproduce;
	double reproduceClock;
	void setDebug(bool debug);
	void canEat(LivingEntity* livingEntity);
	void beConsumed() override;

private:
	bool debug;
	std::vector<LivingEntity*> entitiesInVision;
	double internalClock;
	double thinkClock;
	NeuralGenome* neuralGenome;

	void updateInternalClocks(double deltaTime);
	bool canThink();
	LivingEntity* processVision(std::vector<Creature*>& creatureList, std::vector<Plant*>& plantList);
	bool isEntityInVision(LivingEntity* livingEntity, double& distance, double& angle);
	bool isEntityWithinViewDistance(LivingEntity* livingEntity, double& distance);
	bool isEntityWithinFOV(LivingEntity* livingEntity, double& angle);
	double rateEntityImportance(LivingEntity* livingEntity, double distance, double angle);
};