#pragma once
#include "mousebuttonevent.h"

namespace engine {
	class MouseButtonUpEvent : public MouseButtonEvent {
	public:
		MouseButtonUpEvent(int b, MouseEventData d) : MouseButtonEvent(b, d) {}
	};
}