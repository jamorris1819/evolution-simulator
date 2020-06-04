#pragma once
#include "keyboardevent.h"

namespace engine {
	class KeyHoldEvent : public KeyboardEvent {
	public:
		KeyHoldEvent(int k) : KeyboardEvent(k) {}
	};
}