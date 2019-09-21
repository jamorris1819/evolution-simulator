#include "input.h"
#include <iostream>
#include "GLFW\glfw3.h"
#include "../render/ui/imgui.h"

std::map<int, int> Input::keyMap;
bool Input::updated;
bool Input::scrolledUp;
bool Input::scrolledDown;
glm::vec2 Input::mouseCoordinates;

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

	updated = true;
}

int Input::getKeyState(int key)
{
	std::map<int, int>::iterator it = keyMap.find(key);
	if (it != keyMap.end())
		return it->second;
	return -1;
}

bool Input::isDown(int key)
{
	// If user is typing into the UI, ignore this.
	ImGuiIO& io = ImGui::GetIO();
	io.KeysDown[io.KeyMap[ImGuiKey_Backspace]] = getKeyState(GLFW_KEY_BACKSPACE);

	if (io.WantCaptureKeyboard) return false;

	int state = getKeyState(key);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::isPressed(int key)
{
	// If user is typing into the UI, ignore this.
	ImGuiIO& io = ImGui::GetIO();
	if (io.WantCaptureKeyboard) return false;

	return getKeyState(key) == GLFW_PRESS;
}

bool Input::isUp(int key)
{
	return getKeyState(key) == GLFW_RELEASE;
}

/// Mouse related methods.

void Input::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	// If user is hovering over UI, disable zoom.
	ImGuiIO& io = ImGui::GetIO();
	if (io.WantCaptureMouse) return;

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

void Input::mouseMoveCallback(GLFWwindow* window, double x, double y)
{
	mouseCoordinates = glm::vec2(x, y);
}
