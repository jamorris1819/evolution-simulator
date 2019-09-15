#pragma once
#include "../src/creature/body.h"
#include "GLFW\glfw3.h"
#include "../src/genetics/genome.h"
#include "../src/neural/neuralgenome.h"
#include "../src/neural/netdata.h"
#include "../../creature/creature.h"
#include "../camera.h"

class Menu
{
public:
	static void initialise(GLFWwindow* window);
	static void renderUI();
	static void destroy();
	static void focusGenome(Genome* genome);
	static void focusBody(Body* body);
	static void focusNeuralGenome(NeuralGenome* neuralGenome);
	static void focusLivingEntity(LivingEntity* livingEntity);
	static Camera* camera;
private:
	Menu();
	static void renderOverlay();
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
	static void renderLivingEntityDetails();
	static void triggerBodyRegen();
	static bool* bWindowCreature;
	static Genome* selectedGenome;
	static Body* selectedBody;
	static LivingEntity* selectedLivingEntity;
	static NeuralGenome* selectedNeuralGenome;
	static NeuralGenome* selectedNeuralGenome1;
	static NeuralGenome* selectedNeuralGenome2;
	static NeuralGenome* selectedNeuralGenome3;
	static NetData* netData;
};