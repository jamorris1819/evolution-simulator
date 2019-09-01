#include "livingentity.h"

LivingEntity::LivingEntity(glm::vec3 position) : DrawnEntity(position) {
	maxHealth = 100.0;
	maxEnergy = 100.0;

	alive = true;

	health = maxHealth;
	energy = maxEnergy;
	livingCost = 1;
	movementCost = 0;
}

LivingEntity::~LivingEntity()
{

}

void LivingEntity::update(double deltaTime)
{
	DrawnEntity::update(deltaTime);

	if (!alive) return;

	energy -= (livingCost + movementCost) *deltaTime;

	if (health <= 0) { kill(); }
	if (energy <= 0) { kill(); }

	movementCost = 0; // reset
}

void LivingEntity::kill()
{
	// TODO
	alive = false;
	health = 0;
	energy = 0;
}

void LivingEntity::setHealth(double health)
{
	this->health = health;
}

double LivingEntity::getHealth()
{
	return health;
}

void LivingEntity::setEnergy(double energy)
{
	this->energy = energy;
}

double LivingEntity::getEnergy()
{
	return energy;
}

double LivingEntity::getMaxHealth()
{
	return maxHealth;
}

double LivingEntity::getMaxEnergy()
{
	return maxEnergy;
}

void LivingEntity::setLivingCost(double livingCost)
{
	this->livingCost = livingCost;
}

void LivingEntity::setMovementCost(double movementCost)
{
	this->movementCost = movementCost;
}

bool LivingEntity::isAlive() {
	return alive;
}