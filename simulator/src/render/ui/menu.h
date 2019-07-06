#pragma once
#include "../src/creature/body.h"
#include "GLFW\glfw3.h"
#include "../src/genetics/genome.h"

class Menu
{
public:
	static void initialise(GLFWwindow* window);
	static void renderUI();
	static void destroy();
	static void focusGenome(Genome* genome);
	static void focusBody(Body* body);
private:
	Menu();
	static void renderMenuBar();
	static void renderGenomeDescription();
	static void renderGenomeDetails();
	static void renderTraitsDescription();
	static void renderTraitsDetails();
	static void renderBodyDescription();
	static void renderBodyDetails();
	static void renderCreatureWindow();
	static void triggerBodyRegen();
	static bool* bWindowCreature;
	static Genome* selectedGenome;
	static Body* selectedBody;
};