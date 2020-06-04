#pragma once
#include "mouseevent.h"

namespace engine {
	class MouseButtonEvent : public MouseEvent {
	public:
		MouseButtonEvent(int b) : button(b) {}
		int button;
	};
}