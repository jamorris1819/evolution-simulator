#pragma once
#include "event.h"
#include "mouseeventdata.h"

namespace engine {
	class MouseEvent : public Event {
	public:
		MouseEvent(MouseEventData d) : data(d) {}
		MouseEventData data;
	};
}