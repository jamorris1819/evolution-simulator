#include "creature.h"
#include "creaturebody.h"
#include "contactlistener.h"

Creature::Creature(GLuint shader, glm::vec2 position) : LivingEntity(shader, glm::vec3(position, 0.0f)) {
	genome = nullptr;
	neuralGenome = nullptr;
	//body = new CreatureBody(shader, world);
	internalClock = 0;
	thinkClock = 0;
	canReproduce = false;
	reproduceClock = 0;
	eatCooldown = 0.5;
	eatClock = 0;
	setLivingCost(10);

	viewDistance = 20.0;
	viewAngle = 45.0;
}

Creature::~Creature() {
	delete genome;
}

void Creature::setNeuralGenome(NeuralGenome* neuralGenome) {
	this->neuralGenome = neuralGenome;
}

NeuralGenome* Creature::getNeuralGenome() {
	return neuralGenome;
}

void Creature::generate() {
	if (genome == nullptr) throw std::exception("no genome specified");

	CreatureBody body(genome);
	body.generate();
	setVertexArray(body.getVertexArray());

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
	/*CreatureBody* castBody = (CreatureBody*)body;
	castBody->setRGB(r, g, b);
	castBody->setNoiseOffset(offsetX, offsetY);
	castBody->setNoiseParams(steps, noiseType, octaves);
	castBody->generate();
	castBody->setPosition(getPosition());
	castBody->load();*/

	LivingEntity::generate();
}

void Creature::updateInternalClocks(double deltaTime) {
	internalClock += deltaTime;
	thinkClock += deltaTime;
	reproduceClock += deltaTime;
	eatClock += deltaTime;

	canReproduce = reproduceClock > 5;
}

bool Creature::canThink() {
	bool canThink = thinkClock > 0.1;

	if (canThink) thinkClock = 0;

	return canThink;
}

bool Creature::canEat() {
	bool canEat = eatClock > eatCooldown;

	if (canEat) eatClock = 0;

	return canEat;
}

LivingEntity* Creature::processVision(std::vector<LivingEntity*>& entityList, double& distance, double& angle) {
	LivingEntity* focusedEntity = nullptr;
	double topScore = 0.0f;
	double topDistance = 0.0;
	double topAngle = 0.0;

	double tempDistance = 0.0;
	double tempAngle = 0.0;

	entitiesInVision.clear();
	entitiesInVision.reserve(32);

	for (int i = 0; i < entityList.size(); i++) {
		LivingEntity* entity = entityList[i];
		if (entity == this) continue;
		if (!isEntityInVision(entity, tempDistance, tempAngle)) continue;

		double entityImportance = rateEntityImportance(entity, tempDistance, tempAngle);

		entitiesInVision.push_back(entity);

		if (entityImportance > topScore) {
			focusedEntity = entity;
			topScore = entityImportance;
			topDistance = tempDistance;
			topAngle = tempAngle;
		}
	}

	distance = topDistance;
	angle = topAngle;
	return focusedEntity;
}

bool Creature::isEntityWithinViewDistance(LivingEntity* livingEntity, double& distance) {
	// We avoid sqrt in order to optimise.
	double viewDistanceSqr = pow(viewDistance, 2);
	double distanceSqr =
		(double)pow(livingEntity->getPosition().x - getPosition().x, 2)
		+ (double)pow(livingEntity->getPosition().y - getPosition().y, 2);
	distance = distanceSqr;

	return distanceSqr <= viewDistanceSqr;
}

bool Creature::isEntityWithinFOV(LivingEntity* livingEntity, double& angle) {
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

	double fieldOfView = viewAngle;

	if (debug) {
		int a = 0;
		a++;
		//cout << angle << endl;
	}

	return glm::abs(angle) <= fieldOfView;
}

double Creature::rateEntityImportance(LivingEntity* livingEntity, double distance, double angle) {
	double redInput = 0;
	double greenInput = 0;
	double blueInput = 0;

	/*if (livingEntity != nullptr) {
		redInput = livingEntity->body->r / 255.0;
		greenInput = livingEntity->body->g / 255.0;
		blueInput = livingEntity->body->b / 255.0;
	}*/

	double* inputs = new double[4]{
		redInput,
		greenInput,
		blueInput,
		1.0 - (distance / glm::pow(viewDistance, 2) > 0 ? distance / glm::pow(viewDistance, 2) : 1.0)
	};

	double* decision = neuralGenome->evaluate(inputs);
	delete[] inputs;

	return decision[0];
}

bool Creature::isEntityInVision(LivingEntity* livingEntity, double& distance, double& angle) {
	if (livingEntity == this) return false;

	return isEntityWithinViewDistance(livingEntity, distance)
		&& isEntityWithinFOV(livingEntity, angle);
}

void Creature::update(double deltaTime, std::vector<LivingEntity*>& entityList) {
	LivingEntity::update(deltaTime, entityList);
	updateInternalClocks(deltaTime);

	//if (debug) cout << (isInWater() ? "in water" : "on land") << endl;

	// Check if enough time has passed to think again.
	if (!canThink()) return;

	// Process the entities and decide which one is most worthy of attention.
	double distance = 0;
	double angle = 0;
	LivingEntity* focusedEntity = processVision(entityList, distance, angle);
	if (neuralGenome == nullptr) return;
	// Think

	// Process decision.
	/*if (decision[0] > 0.65) body->turnLeft(0.4f);
	if (decision[1] > 0.65) body->turnRight(0.4f);
	if (decision[2] > 0.5) {
		double power = (decision[2] - 0.5) / 0.5;
		moveForward(power);
	}*/
}

void Creature::moveForward(double power) {
	if (!isAlive()) return;
	//body->moveForward(power);
	setMovementCost(10.0 * power);
}

void Creature::setDebug(bool debug) {
	this->debug = debug;
}

void Creature::consume() {
	if (!canEat() || contactEntity == nullptr) return;

	contactEntity->beConsumed();
	setEnergy(getEnergy() + 10);
}

double Creature::beConsumed() {
	return 0;
}

void Creature::setContactEntity(LivingEntity* livingEntity) {
	this->contactEntity = livingEntity;
}

void Creature::clearContactEntity() {
	contactEntity = nullptr;
}