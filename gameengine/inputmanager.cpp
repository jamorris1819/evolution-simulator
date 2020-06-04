#include "pch.h"
#include "inputmanager.h"
#include <iostream>
#include "keydownevent.h"
#include "keyupevent.h"
#include "keyholdevent.h"

namespace engine {
	EventBus* InputManager::eventBus;

	void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS)
			eventBus->publish(new KeyDownEvent(key));
		else if (action == GLFW_RELEASE)
			eventBus->publish(new KeyUpEvent(key));

		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			eventBus->publish(new KeyHoldEvent(key));
	}
}