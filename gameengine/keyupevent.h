#pragma once
#include "keyboardevent.h"

namespace engine {
	class KeyUpEvent : public KeyboardEvent {
	public:
		KeyUpEvent(int k) : KeyboardEvent(k) {}
	};
}