#pragma once
#include "GLFW\glfw3.h"

class Menu
{
public:
	static void initialise(GLFWwindow* window);
	static void renderUI();
	static void destroy();
private:
	Menu();
	static void renderMenuBar();
};