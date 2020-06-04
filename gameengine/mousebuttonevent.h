#pragma once
#include "mouseevent.h"

namespace engine {
	class MouseButtonEvent : public MouseEvent {
	public:
		MouseButtonEvent(int b, MouseEventData d) : MouseEvent(d), button(b) {}
		int button;
	};
}