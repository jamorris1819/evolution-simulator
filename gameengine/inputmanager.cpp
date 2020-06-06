#include "pch.h"
#include "inputmanager.h"
#include <iostream>
#include "events.h"
#include "uimanager.h"

namespace engine {
	EventBus* InputManager::eventBus;
	MouseEventData InputManager::mouseData;

	void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS)
			eventBus->publish(new KeyDownEvent(key));
		else if (action == GLFW_RELEASE)
			eventBus->publish(new KeyUpEvent(key));

		if (action == GLFW_PRESS || action == GLFW_REPEAT)
			eventBus->publish(new KeyHoldEvent(key));
	}

	void InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		if (action == GLFW_RELEASE)
			eventBus->publish(new MouseButtonUpEvent(button, mouseData));

		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureMouse) return;

		if (action == GLFW_PRESS)
			eventBus->publish(new MouseButtonDownEvent(button, mouseData));
	}

	void InputManager::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
		// Check if any buttons are being used to drag. Send events if so.
		dragCallback(window, xpos, ypos);

		mouseData.x = xpos;
		mouseData.y = ypos;
	}

	void InputManager::dragCallback(GLFWwindow* window, double xpos, double ypos) {
		int buttons[3] = {
			GLFW_MOUSE_BUTTON_LEFT,
			GLFW_MOUSE_BUTTON_RIGHT,
			GLFW_MOUSE_BUTTON_MIDDLE
		};

		int dx = xpos - mouseData.x;
		int dy = ypos - mouseData.y;

		for (int button : buttons) {
			if (glfwGetMouseButton(window, button) == GLFW_PRESS)
				eventBus->publish(new MouseDragEvent(dx, dy, button, mouseData));
		}
	}

	void InputManager::scrollCallback(GLFWwindow* window, double xpos, double ypos) {
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureMouse) return;

		eventBus->publish(new MouseScrollEvent(xpos, ypos, mouseData));
	}
}