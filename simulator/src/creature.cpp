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
	eatCooldown = 0.5;
	eatClock = 0;
	setLivingCost(10);
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

	LivingEntity::generate();
}

void Creature::updateInternalClocks(double deltaTime)
{
	internalClock += deltaTime;
	thinkClock += deltaTime;
	reproduceClock += deltaTime;
	eatClock += deltaTime;

	canReproduce = reproduceClock > 5;
}

bool Creature::canThink()
{
	bool canThink = thinkClock > 0.1;

	if (canThink) thinkClock = 0;

	return canThink;
}

bool Creature::canEat()
{
	bool canEat = eatClock > eatCooldown;

	if (canEat) eatClock = 0;

	return canEat;
}

LivingEntity* Creature::processVision(std::vector<Creature*>& creatureList, std::vector<Plant*>& plantList)
{
	LivingEntity* focusedEntity = nullptr;
	double topScore = 0.0f;
	double distance = 0.0;
	double angle = 0.0;

	for (int i = 0; i < creatureList.size(); i++) {
		LivingEntity* entity = creatureList[i];
		if (entity == this) continue;
		if (!isEntityInVision(entity, distance, angle)) continue;
		
		double entityImportance = rateEntityImportance(entity, distance, angle);

		if (entityImportance > topScore) {
			focusedEntity = entity;
			topScore = entityImportance;
		}
	}

	return focusedEntity;
}

bool Creature::isEntityWithinViewDistance(LivingEntity* livingEntity, double& distance)
{
	// We avoid sqrt in order to optimise.
	double viewDistance = 10; // TODO: replace with gene value.
	double viewDistanceSqr = pow(viewDistance, 2);
	double distanceSqr =
		(double)pow(livingEntity->getPosition().x - getPosition().x, 2)
		+ (double)pow(livingEntity->getPosition().y - getPosition().y, 2);
	distance = distanceSqr;

	return distanceSqr <= viewDistanceSqr;
}

bool Creature::isEntityWithinFOV(LivingEntity* livingEntity, double& angle)
{
	// Calculate the direction vectors.
	double rotation = getRotation();
	glm::vec2 viewDir = glm::vec2(glm::sin(rotation), glm::cos(rotation));
	glm::vec2 entityDir = glm::vec2(
		livingEntity->getPosition().x - getPosition().x,
		livingEntity->getPosition().y - getPosition().y
	);

	entityDir = glm::normalize(entityDir);

	// Calculate angle
	double dot = (double)entityDir.x * viewDir.x + (double)entityDir.y * viewDir.y;
	double det = (double)entityDir.x * viewDir.y - (double)entityDir.y * viewDir.x;
	angle = atan2(det, dot);
	angle *= (180.0 / 3.141582653); // Convert to degrees.

	double fieldOfView = 45.0;

	return angle <= fieldOfView;
}

double Creature::rateEntityImportance(LivingEntity* livingEntity, double distance, double angle)
{
	return 1.0;
}

bool Creature::isEntityInVision(LivingEntity* livingEntity, double& distance, double& angle)
{
	if (livingEntity == this) return false;

	return isEntityWithinViewDistance(livingEntity, distance)
		&& isEntityWithinFOV(livingEntity, angle);
}

void Creature::update(double deltaTime, std::vector<Creature*>& creatureList, std::vector<Plant*>& plantList)
{
	LivingEntity::update(deltaTime);
	updateInternalClocks(deltaTime);

	// Check if enough time has passed to think again.
	if (!canThink()) return;

	// Process the entities and decide which one is most worthy of attention.
	LivingEntity* focusedEntity = processVision(creatureList, plantList);

	
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
	/*if (decision[0] > 0.65) body->turnLeft(0.4f);
	if (decision[1] > 0.65) body->turnRight(0.4f);
	if (decision[2] > 0.5) {
		double power = (decision[2] - 0.5) / 0.5;
		moveForward(power);
	}*/

	delete[] decision;
}

void Creature::moveForward(double power)
{
	if (!isAlive()) return;
	body->moveForward(power);
	setMovementCost(10.0 * power);
}

void Creature::setDebug(bool debug)
{
	this->debug = debug;
}

void Creature::consume()
{
	if (!canEat() || contactEntity == nullptr) return;

	contactEntity->beConsumed();
	setEnergy(getEnergy() + 10);
	cout << "eaten" << endl;
}

double Creature::beConsumed()
{
	return 0;
}

void Creature::setContactEntity(LivingEntity* livingEntity)
{
	this->contactEntity = livingEntity;
}

void Creature::clearContactEntity()
{
	contactEntity = nullptr;
}
