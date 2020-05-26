#pragma once
#include "component.h"
#include "glm/vec2.hpp"

namespace engine {
	class VelocityComponent : public Component {
	public:
		VelocityComponent() : VelocityComponent(glm::vec2(0, 0)) {}
		VelocityComponent(glm::vec2 vel) : velocity(vel) {}
		virtual ComponentType getType() const override { return ComponentType::VELOCITY; }
		glm::vec2 velocity;
	};
}