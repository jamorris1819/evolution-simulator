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
	static void focusTerrainManager(TerrainManager* terrainManager);
	static Camera* camera;
	static EntityManager* entityManager;
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
	static void renderWorldEditor();
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
	static TerrainManager* terrain;

	static bool* worldEditorOpen;
};