#pragma once
#include "drawnentity.h"

class LivingEntity : public DrawnEntity {
public:
	LivingEntity(glm::vec3 position);
	~LivingEntity();
	virtual void update(double deltaTime);
	void kill();
	bool isAlive();
	double getHealth();
	double getEnergy();
	double getMaxHealth();
	double getMaxEnergy();

protected:
	void setHealth(double health);
	void setEnergy(double energy);

	void setLivingCost(double livingCost);
	double getLivingCost();
	void setMovementCost(double movementCost);

private:
	double maxHealth;
	double maxEnergy;
	double health;
	double energy;
	double livingCost; // the amount of energy required per update.
	double movementCost; // a variable amount depending on what the living entity is doing.
	bool alive;
};