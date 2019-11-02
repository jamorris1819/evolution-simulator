#define GLEW_STATIC

#include <iostream>
#include "shaderutility.h"
#include <vector>
#include "vertex.h"
#include "vertexarrayobject.h"
#include "drawnentity.h"
#include "camera.h"
#include "input.h"
#include <Windows.h>

#include "menu.h"
#include "gene.h"
#include "genome.h"
#include "genemarker.h"
#include <ctime>
#include "FastNoise.h"
#include "Box2D.h"
#include "creature.h"
#include "neuralgenome.h"
#include "contactlistener.h"
#include "entitymanager.h"
#include <thread>
#include <time.h>
#include "hex.h"
#include "terrainmanager.h"
#include "plant.h"
#include "worldwindow.h"
#include "creaturewindow.h"
#include "bushbody.h"

using namespace std;

GLuint program;
GLFWwindow* window;
float lastTime;
float width = 1920.0f;
float height = 1080.0f;
double* frequency;
double counter;

EntityManager* entityManager;

Body* body;
Camera* cam;
b2World* world;
ContactListener* contactListener;
vector<Hex*> terr;
TerrainManager* terrain;
Menu* menu;


void initialiseEntities() {
	srand(time(NULL));
	// Initialise entity manager and create a test creature.
	entityManager = new EntityManager(program, world);

	/*for (int i = 0; i < 100; i++) {
		int x = (rand() % 400);
		int y = (rand() % 400);
		entityManager->createRandomCreature(glm::vec2(x, y));
	}*/
	
	
	entityManager->createPlant(glm::vec2(160, 100));
	entityManager->createRandomCreature(glm::vec2(150, 100));
	entityManager->createRandomCreature(glm::vec2(150, 120));
	entityManager->getTestCreature()->setDebug(true);

	int size = 4;

	terrain = new TerrainManager(program);
	terrain->generate(50, 50, 8);
	terrain->paintTerrain();

	// Initialise camera.
	cam = new Camera(glm::vec2(0, 0), program);
	cam->initialise(width, height, 20.0f);
	cam->position = -entityManager->getTestCreature()->getPosition();
	counter = 0;
}

double getTime()
{
	return GetTickCount();
}

void initialiseBox2D()
{
	b2Vec2 gravity(0.0f, 0.0f);
	world = new b2World(gravity);


	// DEBUG BELOW.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(20.0f, 0.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(5.0f, 2.0f);

	// Add the ground fixture to the ground body.
	b2Fixture* groundFixture = groundBody->CreateFixture(&groundBox, 0.0f);
	b2Filter filterData = groundFixture->GetFilterData();
	filterData.categoryBits = ContactType::TERRAIN;
	groundFixture->SetFilterData(filterData);

	std::cout << (ContactType::PLANT | ContactType::CREATURE) << endl;
}

void initialiseUI()
{
	// Initialise UI.
	menu = new Menu();
	menu->initialise(window);

	WorldWindow* worldWindow = new WorldWindow();
	worldWindow->terrain = terrain;
	worldWindow->entityManager = entityManager;
	menu->addWindow(worldWindow);

	CreatureWindow* creatureWindow = new CreatureWindow();
	creatureWindow->creature = entityManager->getTestCreature();
	menu->addWindow(creatureWindow);
}

void initialise()
{
	// Output some data to screen.
	std::cout << "Glew initialisation " << (glewInit() == 0 ? "successful" : "failed") << endl;
	std::cout << "GLFW Version " << glfwGetVersionString() << endl;
	std::cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << endl;
	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	std::cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << endl;
	glViewport(0, 0, width, height);

	// Set up shaders.
	ShaderUtility shaderUtility;
	program = shaderUtility.createProgram((char*)"shaders/vertexshader.glsl", (char*)"shaders/fragmentshader.glsl");
	glPolygonMode(GL_FRONT, GL_POLYGON);
	
	lastTime = getTime();

	initialiseBox2D();
	initialiseEntities();
	initialiseUI();

	contactListener = new ContactListener(entityManager);
	world->SetContactListener(contactListener);

	// Initialise input handler.
	Input::initialise();
	glfwSetKeyCallback(window, Input::keyCallback);
	glfwSetScrollCallback(window, Input::scrollCallback);
	glfwSetCursorPosCallback(window, Input::mouseMoveCallback);

	glfwMaximizeWindow(window);
}

void render() {
	terrain->render();
	entityManager->render();
}

void update() {
	// Calculate delta time.
	double currentTime = getTime();
	double elapsedTime = currentTime - lastTime;
	double deltaTime = abs(elapsedTime * 0.001);
	lastTime = currentTime;
	counter += deltaTime;

	cam->update(deltaTime);
	entityManager->update(deltaTime);
	terrain->update(deltaTime);

	// Update the physics simulation.
	world->Step(1.0f / 60.0f, 6, 2);

	// Debug creature controller.
	if (Input::isDown(GLFW_KEY_UP)) {
		entityManager->getTestCreature()->moveForward(0.6f);
	}

	if (Input::isPressed(GLFW_KEY_DOWN)) {
		entityManager->getTestCreature()->moveForward(-0.6f);
	}

	if (Input::isDown(GLFW_KEY_LEFT)) {
		entityManager->getTestCreature()->body->turnLeft(0.75f);
	}

	if (Input::isDown(GLFW_KEY_RIGHT)) {
		entityManager->getTestCreature()->body->turnRight(0.75f);
	}

	if (Input::isPressed(GLFW_KEY_SPACE)) {
		entityManager->getTestCreature()->consume();
	}
}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void window_size_callback(GLFWwindow* window, int w, int h)
{
	width = w;
	height = h;
	glViewport(0, 0, width, height);
	cam->updateWindowBounds(width, height);
}

int main(int argc, char **argv)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	glfwSetErrorCallback(error_callback);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Evolution Simulator", NULL, NULL);
	glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetWindowPos(window, (3440.0f - width) / 2, (1440.0f - height) / 2);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	
	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	initialise();

	bool showDemo = true;
	glfwSwapInterval(1);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		update();
		render();

		menu->render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	menu->unload();
	return 0;
}