#pragma once
#include "mouseevent.h"

namespace engine {
	class MouseScrollEvent : public MouseEvent {
	public:
		MouseScrollEvent(double x, double y, MouseEventData d) : MouseEvent(d), dx(x), dy(y) {}
		double dx;
		double dy;
	};
}