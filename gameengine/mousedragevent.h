#pragma once
#include "mouseevent.h"

namespace engine {
	class MouseDragEvent : public MouseEvent {
	public:
		MouseDragEvent(double x, double y, int b, MouseEventData d) : MouseEvent(d), dx(x), dy(y), button(b) {}
		double dx;
		double dy;
		int button;
	};
}