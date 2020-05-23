#include "livingentity.h"

LivingEntity::LivingEntity(GLuint shaderId, glm::vec3 position) : DrawnEntity(shaderId, position) {
	maxHealth = 100.0;
	maxEnergy = 5000.0;

	alive = true;
	genome = nullptr;
	health = maxHealth;
	energy = maxEnergy;
	livingCost = 1;
	movementCost = 0;
}

LivingEntity::~LivingEntity() {
}

void LivingEntity::update(double deltaTime, std::vector<LivingEntity*>& entityList) {
	DrawnEntity::update(deltaTime);

	if (!alive) return;

	energy -= (livingCost + movementCost) * deltaTime;

	if (health <= 0) { kill(); }
	if (energy <= 0) { kill(); }

	movementCost = 0; // reset
}

void LivingEntity::kill() {
	// TODO
	alive = false;
	health = 0;
	energy = 0;
}

void LivingEntity::setHealth(double health) {
	this->health = health > maxHealth ? maxHealth : health;
}

double LivingEntity::getHealth() {
	return health;
}

void LivingEntity::setEnergy(double energy) {
	this->energy = energy > maxEnergy ? maxEnergy : energy;
}

double LivingEntity::getEnergy() {
	return energy;
}

double LivingEntity::getMaxHealth() {
	return maxHealth;
}

double LivingEntity::getMaxEnergy() {
	return maxEnergy;
}

void LivingEntity::setLivingCost(double livingCost) {
	this->livingCost = livingCost;
}

Genome* LivingEntity::getGenome() {
	return genome;
}

void LivingEntity::setGenome(Genome* genome) {
	this->genome = genome;
}

bool LivingEntity::isInWater() {
	return inWater;
}

void LivingEntity::setInWater(bool inWater) {
	this->inWater = inWater;
}

void LivingEntity::setMovementCost(double movementCost) {
	this->movementCost = movementCost;
}

void LivingEntity::generate() {
	// IMPORTANT
	/*b2Body* rBody = body->getPhysicsBody();
	for (b2Fixture* b = rBody->GetFixtureList(); b; b = b->GetNext()) {
		b->SetUserData(this);
	}*/
}

bool LivingEntity::isAlive() {
	return alive;
}