#pragma once
#include "mousebuttonevent.h"

namespace engine {
	class MouseButtonDownEvent : public MouseButtonEvent {
	public:
		MouseButtonDownEvent(int b) : MouseButtonEvent(b) {}
	};
}