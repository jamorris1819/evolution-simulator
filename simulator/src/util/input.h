#pragma once
#include "GLFW\glfw3.h"
#include <map>
#include <glm\ext\vector_float2.hpp>

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
	static void mouseMoveCallback(GLFWwindow* window, double x, double y);
	static GLFWwindow* glfwWindow;
	static glm::vec2 mouseCoordinates;
protected:
	Input();
	static std::map<int, int> keyMap;
	static bool updated;
	static bool scrolledUp;
	static bool scrolledDown;
	static int getKeyState(int key);
};