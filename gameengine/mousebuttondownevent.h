#pragma once
#include "mousebuttonevent.h"

namespace engine {
	class MouseButtonDownEvent : public MouseButtonEvent {
	public:
		MouseButtonDownEvent(int b, MouseEventData d) : MouseButtonEvent(b, d) {}
	};
}