#pragma once
#include "body.h"
#include "genome.h"
#include "livingentity.h"
#include "glm\vec2.hpp"
#include "neuralgenome.h"

class Creature : public LivingEntity
{
public:
	Creature(GLuint shader, b2World* world, glm::vec2 position);
	~Creature();
	void setNeuralGenome(NeuralGenome* neuralGenome);
	NeuralGenome* getNeuralGenome();
	void generate();
	void update(double deltaTime);
	void moveForward(double power);
	bool canReproduce;
	double reproduceClock;

private:
	double internalClock;
	double thinkClock;
	NeuralGenome* neuralGenome;
};