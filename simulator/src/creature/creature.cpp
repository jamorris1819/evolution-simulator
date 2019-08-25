#include "creature.h"

Creature::Creature(GLuint shader, b2World* world, glm::vec2 position) : DrawnEntity(glm::vec3(position, 0.0f))
{
	genome = nullptr;
	body = new Body(shader, world);
	internalClock = 0;
}

Creature::~Creature()
{
	delete genome;
}

void Creature::setGenome(Genome* genome)
{
	this->genome = genome;
}

void Creature::setNeuralGenome(NeuralGenome* neuralGenome)
{
	this->neuralGenome = neuralGenome;
}

Genome* Creature::getGenome()
{
	return genome;
}

NeuralGenome* Creature::getNeuralGenome()
{
	return neuralGenome;
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

void Creature::update(double deltaTime)
{
	DrawnEntity::update(deltaTime);

	internalClock += deltaTime;

	if (neuralGenome == nullptr) return;
	return;
	// Think
	float* inputs = new float[4]{ (float)sin(internalClock), (float)cos(internalClock + 1), (float)cos(internalClock + 10), 1 };
	float* decision = neuralGenome->evaluate(inputs);
	delete inputs;

	// Process decision.
	cout << decision << endl;

	if (decision[0] > 0.85f) body->turnLeft();
	if (decision[1] > 0.85f) body->turnRight();
	if (decision[2] > 0.25f) {
		float power = (decision[2] - 0.25f) / 0.75f;
		body->moveForward(power);
	}

	delete decision;
}