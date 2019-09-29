#include "creature.h"
#include "creaturebody.h"
#include "contactlistener.h"

Creature::Creature(GLuint shader, b2World* world, glm::vec2 position) : LivingEntity(glm::vec3(position, 0.0f))
{
	genome = nullptr;
	neuralGenome = nullptr;
	body = new CreatureBody(shader, world);
	internalClock = 0;
	thinkClock = 0;
	canReproduce = false;
	reproduceClock = 0;
}

Creature::~Creature()
{
	delete genome;
}

void Creature::setNeuralGenome(NeuralGenome* neuralGenome)
{
	this->neuralGenome = neuralGenome;
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
	CreatureBody* castBody = (CreatureBody*)body;
	castBody->setRGB(r, g, b);
	castBody->setNoiseOffset(offsetX, offsetY);
	castBody->setNoiseParams(steps, noiseType, octaves);
	castBody->generate();
	castBody->setPosition(getPosition());
	castBody->load();

	// Give all fixtures a pointer to the creature.
	b2Body* rBody = castBody->getPhysicsBody();
	for (b2Fixture* b = rBody->GetFixtureList(); b; b = b->GetNext()) {
		b->SetUserData(this);
	}
}

void Creature::update(double deltaTime)
{
	LivingEntity::update(deltaTime);

	internalClock += deltaTime;
	thinkClock += deltaTime;
	reproduceClock += deltaTime;

	canReproduce = reproduceClock > 5;

	if (thinkClock < 0.1) {
		return;
	}

	thinkClock = 0;

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
	delete[] inputs;

	// Process decision.
	if (decision[0] > 0.65) body->turnLeft(0.4f);
	if (decision[1] > 0.65) body->turnRight(-0.4f);
	if (decision[2] > 0.5) {
		double power = (decision[2] - 0.5) / 0.5;
		moveForward(power);
	}

	delete[] decision;
}

void Creature::moveForward(double power)
{
	if (!isAlive()) return;
	body->moveForward(power);
	setMovementCost(10.0 * power);
}