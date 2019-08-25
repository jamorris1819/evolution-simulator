#include <iostream>
#include "util\shaderutility.h"
#include <vector>
#include "render\vertex.h"
#include "render\vertexarrayobject.h"
#include "entities\drawnentity.h"
#include "render\camera.h"
#include "util\input.h"

#include "render\ui\menu.h"
#include "genetics\gene.h"
#include "genetics\genome.h"
#include "genetics\genemarker.h"
#include <ctime>
#include "noise\FastNoise.h"
#include "Box2D\Box2D.h"
#include "creature\creature.h"
#include "neural\neuralgenome.h"

using namespace std;

GLuint program;
GLFWwindow* window;
float lastTime;
float width = 1920.0f;
float height = 1080.0f;
double* frequency;

Creature* creature;
Body* body;
Camera* cam;
b2World* world;
NeuralGenome* neuralGenome;

void initialiseEntities() {
	creature = new Creature(program, world, glm::vec2(0, 0));
	Genome* gen = new Genome(true);
	creature->setGenome(gen);
	creature->generate();

	neuralGenome = new NeuralGenome(4, 3);

	creature->setNeuralGenome(neuralGenome);

	Menu::focusBody(creature->body);
	Menu::focusGenome(gen);
	Menu::focusNeuralGenome(neuralGenome);



	cam = new Camera(glm::vec2(0, 0), program);
	cam->initialise(width, height, 20.0f);
}

double getTime()
{
	return 0;
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
	groundBody->CreateFixture(&groundBox, 0.0f);
}

void initialise()
{
	// Output some data to screen.
	cout << "Glew initialisation " << (glewInit() == 0 ? "successful" : "failed") << endl;
	cout << "GLFW Version " << glfwGetVersionString() << endl;
	cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << endl;
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << endl;
	glViewport(0, 0, width, height);

	// Set up shaders.
	ShaderUtility shaderUtility;
	program = shaderUtility.createProgram((char*)"src/Shaders/vertexshader.glsl", (char*)"src/Shaders/fragmentshader.glsl");
	glPolygonMode(GL_FRONT, GL_POLYGON);
	
	lastTime = getTime();

	// Initialise UI.
	Menu::initialise(window);

	initialiseBox2D();
	initialiseEntities();

	// Initialise input handler.
	Input::initialise();
	glfwSetKeyCallback(window, Input::keyCallback);
	glfwSetScrollCallback(window, Input::scrollCallback);
	

	//for (int i = 0; i < 100000; i++) {
		//Gene<int>* g = a->getGene<int>(GeneMarker::GM_SIZE, 0);
		//delete size;
	//}
}

void render() {
	creature->render();
}

void update() {
	// Calculate delta time.
	double currentTime = getTime();
	double elapsedTime = currentTime - lastTime;
	double deltaTime = elapsedTime * 0.001;
	lastTime = currentTime;
	deltaTime = 0.013;

	cam->update(deltaTime);
	//de->update(deltaTime);
	creature->update(deltaTime);

	// Update the physics simulation.
	world->Step(1.0f / 60.0f, 6, 2);

	// Debug creature controller.
	if (Input::isDown(GLFW_KEY_UP)) {
		creature->body->moveForward(1.0f);
	}

	if (Input::isDown(GLFW_KEY_LEFT)) {
		creature->body->turnLeft();
	}

	if (Input::isDown(GLFW_KEY_RIGHT)) {
		creature->body->turnRight();
	}

	// test evolution

	/*body->unload();
	body->offsetX += deltaTime * 0.1f;
	body->generate();
	body->load();*/
}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
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

		Menu::renderUI();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	Menu::destroy();
	return 0;
}