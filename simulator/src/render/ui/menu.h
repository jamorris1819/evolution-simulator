#pragma once
#include "GLFW\glfw3.h"
#include "../src/genetics/genome.h"

class Menu
{
public:
	static void initialise(GLFWwindow* window);
	static void renderUI();
	static void destroy();
	static void focusGenome(Genome* genome);
private:
	Menu();
	static void renderMenuBar();
	static void renderGenome();
	static void renderCreatureWindow();
	static bool* bWindowCreature;
	static Genome* selectedGenome;
};