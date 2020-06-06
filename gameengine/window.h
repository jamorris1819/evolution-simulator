#pragma once
#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <string>
#include <functional>
#include "inputmanager.h"

namespace engine {
	class Window {
	public:
		Window(std::string t, int w, int h)
			: title(t), width(w), height(h), window(nullptr){}
		~Window();
		void initialise();
		int getWidth() const { return width; }
		int getHeight() const { return height; }
		bool isOpen();
		void beginRender();
		void endRender();
		void registerInputHandler(InputManager& manager);
		std::string getTitle() const { return title; }
		GLFWwindow* getWindow() const { return window; }
	private:
		GLFWwindow* window;
		std::string title;
		int width;
		int height;
	};
}