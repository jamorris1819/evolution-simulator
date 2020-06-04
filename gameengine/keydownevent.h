#pragma once
#include "keyboardevent.h"

namespace engine {
	class KeyDownEvent : public KeyboardEvent {
	public:
		KeyDownEvent(int k) : KeyboardEvent(k) {}
	};
}