#include "creature.h"

Creature::Creature(GLuint shader, b2World* world, glm::vec2 position) : DrawnEntity(glm::vec3(position, 0.0f))
{
	genome = nullptr;
	body = new Body(shader, world);
}

Creature::~Creature()
{
	delete genome;
}

void Creature::setGenome(Genome* genome)
{
	this->genome = genome;
}

Genome* Creature::getGenome()
{
	return genome;
}

void Creature::generate()
{
	if (genome == nullptr) throw exception("no genome specified");

	// Pull data from the genome.
	int steps = genome->getGeneValue<int>(GeneMarker::GM_BODY_STEPS);
	int noiseType = 4;
	int octaves = 5;
	float offsetX = genome->getGeneValue<float>(GeneMarker::GM_BODY_OFFSETX);
	float offsetY = genome->getGeneValue<float>(GeneMarker::GM_BODY_OFFSETY);
	int r = genome->getGeneValue<int>(GeneMarker::GM_COLOUR_R);
	int g = genome->getGeneValue<int>(GeneMarker::GM_COLOUR_G);
	int b = genome->getGeneValue<int>(GeneMarker::GM_COLOUR_B);

	// Generate the body.
	body->addParameters(steps, noiseType, octaves, offsetX, offsetY, r, g, b);
	body->generate();
	body->load();
}