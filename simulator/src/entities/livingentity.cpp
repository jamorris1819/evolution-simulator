#include "livingentity.h"

LivingEntity::LivingEntity(glm::vec3 position) : DrawnEntity(position) {
	maxHealth = 100.0;
	maxEnergy = 100.0;

	alive = true;

	health = maxHealth;
	energy = maxEnergy;
	livingCost = 1;
}

LivingEntity::~LivingEntity()
{

}

void LivingEntity::update(double deltaTime)
{
	DrawnEntity::update(deltaTime);

	if (!alive) return;

	energy -= livingCost * deltaTime;

	if (health <= 0) { kill(); }
	if (energy <= 0) { kill(); }
}

void LivingEntity::kill()
{
	// TODO
	alive = false;
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

bool LivingEntity::isAlive() {
	return alive;
}