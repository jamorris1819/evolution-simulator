#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "eventbus.h"

namespace engine {
	class InputManager {
	public:
		void setWindow(GLFWwindow* w) {
			window = w;
			glfwSetKeyCallback(window, InputManager::keyCallback);
			glfwSetMouseButtonCallback(window, InputManager::mouseButtonCallback);
		}
		static void setEventBus(EventBus* eb) { eventBus = eb; }
	private:
		GLFWwindow* window;
		static EventBus* eventBus;
		static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	};
}