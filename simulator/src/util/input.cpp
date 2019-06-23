#include "input.h"
#include <iostream>
#include "GLFW\glfw3.h"

std::map<int, int> Input::keyMap;
bool Input::updated;
bool Input::scrolledUp;
bool Input::scrolledDown;

Input::Input()
{

}

void Input::initialise()
{
	for (int i = 0; i < 350; i++) keyMap.insert(std::pair<int, int>(i, GLFW_RELEASE));
	updated = false;
}

// Check to see if a change has been made.
bool Input::pollChange()
{
	bool temp = updated;
	updated = false;
	return temp;
}

/// Key related methods.

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	std::map<int, int>::iterator it = keyMap.find(key);
	if (it != keyMap.end())
		it->second = action;

	if (action == GLFW_RELEASE) {
		updated = true;
	}

	updated = true;
}

bool Input::isDown(int key)
{
	std::map<int, int>::iterator it = keyMap.find(key);
	if (it != keyMap.end())
		return it->second == GLFW_PRESS || it->second == GLFW_REPEAT;
	return false;
}

bool Input::isUp(int key)
{
	std::map<int, int>::iterator it = keyMap.find(key);
	if (it != keyMap.end())
		return it->second == GLFW_RELEASE;
	return false;
}

/// Mouse related methods.

void Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	scrolledUp = yoffset > 0;
	scrolledDown = yoffset < 0;
}

bool Input::scrollDown()
{
	bool temp = scrolledDown;
	scrolledDown = false;
	return temp;
}

bool Input::scrollUp()
{
	bool temp = scrolledUp;
	scrolledUp = false;
	return temp;
}