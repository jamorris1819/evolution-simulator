#pragma once
#include "../src/creature/body.h"
#include "GLFW\glfw3.h"
#include "../src/genetics/genome.h"
#include "../src/neural/neuralgenome.h"
#include "../src/neural/netdata.h"

class Menu
{
public:
	static void initialise(GLFWwindow* window);
	static void renderUI();
	static void destroy();
	static void focusGenome(Genome* genome);
	static void focusBody(Body* body);
	static void focusNeuralGenome(NeuralGenome* neuralGenome);
private:
	Menu();
	static void renderMenuBar();
	static void renderGenomeDescription();
	static void renderGenomeDetails();
	static void renderTraitsDescription();
	static void renderTraitsDetails();
	static void renderBodyDescription();
	static void renderBodyDetails();
	static void renderNeuralNetDescription();
	static void renderNeuralNetDetails();
	static void renderCreatureWindow();
	static void triggerBodyRegen();
	static bool* bWindowCreature;
	static Genome* selectedGenome;
	static Body* selectedBody;
	static NeuralGenome* selectedNeuralGenome;
	static NeuralGenome* selectedNeuralGenome1;
	static NeuralGenome* selectedNeuralGenome2;
	static NeuralGenome* selectedNeuralGenome3;
	static NetData* netData;
};