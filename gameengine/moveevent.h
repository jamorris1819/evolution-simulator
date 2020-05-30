#pragma once
#include "event.h"
#include "glm/vec2.hpp"

namespace engine{
	class MoveEvent : public Event {
	public:
		MoveEvent(glm::vec2 mov) : move(mov) {}
		glm::vec2 move;
	};
}