#pragma once
#include "body.h"
#include "GLFW\glfw3.h"
#include "genome.h"
#include "neuralgenome.h"
#include "netdata.h"
#include "creature.h"
#include "terrainmanager.h"
#include "camera.h"
#include "entitymanager.h"
#include "menuwindow.h"

class Menu
{
public:
	Menu();
	void initialise(GLFWwindow* window);
	void render();
	void addWindow(MenuWindow* menuWindow);
	void unload();
private:
	std::vector<MenuWindow*> windows;
	void renderOverlay();
	void renderMenuBar();
};