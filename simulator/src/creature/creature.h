#pragma once
#include "body.h"
#include "../genetics/genome.h"
#include "../entities/livingentity.h"
#include "glm\vec2.hpp"
#include "../neural/neuralgenome.h"

class Creature : public LivingEntity
{
public:
	Creature(GLuint shader, b2World* world, glm::vec2 position);
	~Creature();
	void setGenome(Genome* genome);
	void setNeuralGenome(NeuralGenome* neuralGenome);
	Genome* getGenome();
	NeuralGenome* getNeuralGenome();
	void generate();
	void update(double deltaTime);

private:
	double internalClock;
	Genome * genome;
	NeuralGenome* neuralGenome;
};