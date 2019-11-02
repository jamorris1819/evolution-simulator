#pragma once
#include "drawnentity.h"
#include "genome.h"

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
	Genome* getGenome();
	void setGenome(Genome* genome);
	virtual void beConsumed() = 0;

protected:
	void setHealth(double health);
	void setEnergy(double energy);
	void setLivingCost(double livingCost);
	double getLivingCost();
	void setMovementCost(double movementCost);
	virtual void generate();
	Genome* genome;

private:
	double maxHealth;
	double maxEnergy;
	double health;
	double energy;
	double livingCost; // the amount of energy required per update.
	double movementCost; // a variable amount depending on what the living entity is doing.
	bool alive;
};