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
	void update(double deltaTime, std::vector<LivingEntity*>& entityList);
	void moveForward(double power);
	bool canReproduce;
	double reproduceClock;
	void setDebug(bool debug);
	void consume();
	double beConsumed() override;
	void setContactEntity(LivingEntity* livingEntity);
	void clearContactEntity();

private:
	double eatCooldown;
	double eatClock;
	LivingEntity* contactEntity;
	bool debug;
	std::vector<LivingEntity*> entitiesInVision;
	double internalClock;
	double thinkClock;
	NeuralGenome* neuralGenome;
	double viewDistance;
	double viewAngle;

	void updateInternalClocks(double deltaTime);
	bool canThink();
	bool canEat();
	LivingEntity* processVision(std::vector<LivingEntity*>& entityList, double& distance, double& angle);
	bool isEntityInVision(LivingEntity* livingEntity, double& distance, double& angle);
	bool isEntityWithinViewDistance(LivingEntity* livingEntity, double& distance);
	bool isEntityWithinFOV(LivingEntity* livingEntity, double& angle);
	double rateEntityImportance(LivingEntity* livingEntity, double distance, double angle);
};