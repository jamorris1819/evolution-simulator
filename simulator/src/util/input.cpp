#include "input.h"
#include <iostream>
#include "GLFW\glfw3.h"

std::map<int, int> Input::keyMap;
bool Input::updated;

Input::Input()
{

}

void Input::initialise()
{
	for (int i = 0; i < 350; i++) keyMap.insert(std::pair<int, int>(i, GLFW_RELEASE));
	updated = false;
}

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

// Check to see if a change has been made.
bool Input::pollChange()
{
	bool temp = updated;
	updated = false;
	return temp;
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