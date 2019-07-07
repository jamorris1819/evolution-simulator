#pragma once
#include "body.h"
#include "../genetics/genome.h"
#include "../entities/drawnentity.h"
#include "glm\vec2.hpp"

class Creature : public DrawnEntity
{
public:
	Creature(GLuint shader, b2World* world, glm::vec2 position);
	~Creature();
	void setGenome(Genome* genome);
	Genome* getGenome();
	void generate();

private:
	Genome * genome;
};