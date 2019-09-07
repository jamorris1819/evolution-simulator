#pragma once
#include "GLFW\glfw3.h"
#include <map>

class Input
{
public:
	static void initialise();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static bool pollChange();
	static bool isDown(int key);
	static bool isUp(int key);
	static bool isPressed(int key);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	static bool scrollDown();
	static bool scrollUp();
	static GLFWwindow* glfwWindow;
protected:
	Input();
	static std::map<int, int> keyMap;
	static bool updated;
	static bool scrolledUp;
	static bool scrolledDown;
};