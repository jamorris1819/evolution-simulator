#pragma once
#include "drawnentity.h"
#include "glm/vec3.hpp"

class PhysicsEntity : public DrawnEntity {
public:
	PhysicsEntity(glm::vec3 const& position);
	PhysicsEntity(glm::vec3 const& position, glm::vec3 const& scale);
	~PhysicsEntity();

	virtual glm::vec3 const& getPosition() const override;
	virtual glm::vec3 const& getVelocity() const override;
	virtual glm::vec3 const& getScale() const override;
	virtual float getRotation() const override;

	virtual void setPosition(glm::vec3 position) override;
	virtual void setVelocity(glm::vec3 velocity) override;
	virtual void setScale(glm::vec3 scale) override;
	virtual void setRotation(float rotation) override;
};