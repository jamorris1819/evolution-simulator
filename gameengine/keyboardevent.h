#pragma once
#include "event.h"

namespace engine {
	class KeyboardEvent : public Event {
	public:
		KeyboardEvent(int k) : key(k) {}
		int key;
	};
}