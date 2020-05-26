#pragma once
#include "component.h"
#include "glm/vec2.hpp"

namespace engine {
	class PositionComponent : public Component {
	public:
		PositionComponent() : PositionComponent(glm::vec2(0, 0)) {}
		PositionComponent(glm::vec2 pos) : position(pos) {}
		virtual ComponentType getType() const override { return ComponentType::POSITION; }
		glm::vec2& position;
	};
}