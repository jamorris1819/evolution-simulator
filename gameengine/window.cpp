#include "pch.h"
#include "window.h"

namespace engine {
	Window::~Window() {
	}
	void Window::initialise() {
		if (!glfwInit())
			return;

		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (!window) {
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(window);
		glewInit();
	}

	bool Window::isOpen() {
		return !glfwWindowShouldClose(window);
	}

	void Window::beginRender() {
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::endRender() {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void Window::registerInputHandler(InputManager& manager) {
		manager.setWindow(window);
	}
}