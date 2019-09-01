#include "creature.h"
#include "../util/contactlistener.h"

Creature::Creature(GLuint shader, b2World* world, glm::vec2 position) : LivingEntity(glm::vec3(position, 0.0f))
{
	genome = nullptr;
	neuralGenome = nullptr;
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

	// Give all fixtures a pointer to the creature.
	b2Body* rBody = body->getPhysicsBody();
	for (b2Fixture* b = rBody->GetFixtureList(); b; b = b->GetNext()) {
		b->SetUserData(this);
	}
}

void Creature::update(double deltaTime)
{
	LivingEntity::update(deltaTime);

	internalClock += deltaTime;

	if (neuralGenome == nullptr) return;
	// Think
	double* inputs = new double[5]{
		(sin(internalClock) + 1.0) / 2.0,
		(sin(internalClock + 10) + 1.0) / 2.0,
		(sin(internalClock * 2) + 1.0) / 2.0,
		(sin(internalClock * 27) + 1.0) / 2.0,
		1.0 - ((sin(internalClock) + 1.0) / 2.0)
	};

	double* decision = neuralGenome->evaluate(inputs);
	delete inputs;
	return;

	// Process decision.
	cout << decision[0] << endl;
	if (decision[0] > 0.65) body->turnLeft();
	if (decision[1] > 0.65) body->turnRight();
	if (decision[2] > 0.5) {
		double power = (decision[2] - 0.5) / 0.5;
		body->moveForward(power);
	}

	delete decision;
}