#pragma once
#include "drawnentity.h"

class LivingEntity : public DrawnEntity {
public:
	LivingEntity(glm::vec3 position);
	~LivingEntity();
	void update(double deltaTime);
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

private:
	double maxHealth;
	double maxEnergy;
	double health;
	double energy;
	double livingCost; // the amount of energy required per update.
	bool alive;
};