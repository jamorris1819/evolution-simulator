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

using namespace std;

GLuint program;
GLFWwindow* window;
float lastTime;
float width = 1920.0f;
float height = 1080.0f;
double* frequency;

DrawnEntity* de;
Body* body;
Camera* cam;
b2World* world;

void initialiseEntities() {
	body = new Body(program, world);
	body->addParameters(8, (int)FastNoise::Simplex, 4,0,0, 1, 0, 0);
	body->generate();
	body->load();
	body->setPosition(glm::vec2(400, 400));

	Menu::focusBody(body);

	de = new DrawnEntity(glm::vec3(200, 200, 0));
	de->setPolygon(body);
	de->setBody(body);

	cam = new Camera(glm::vec2(0, 0), program);
	cam->initialise(width, height, 100.0f);

	std::cout << geneMarkerToString(GeneMarker::GM_COLOUR_R) << std::endl;
}

double getTime()
{
	return 0;
}

void initialise()
{
	cout << "Glew initialisation " << (glewInit() == 0 ? "successful" : "failed") << endl;
	cout << "GLFW Version " << glfwGetVersionString() << endl;
	cout << "OpenGL vendor: " << glGetString(GL_VENDOR) << endl;
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	cout << "OpenGL renderer: " << glGetString(GL_RENDERER) << endl;
	glViewport(0, 0, width, height);

	ShaderUtility shaderUtility;
	program = shaderUtility.createProgram((char*)"src/Shaders/vertexshader.glsl", (char*)"src/Shaders/fragmentshader.glsl");
	glPolygonMode(GL_FRONT, GL_POLYGON);
	
	lastTime = getTime();
	Input::initialise();
	glfwSetKeyCallback(window, Input::keyCallback);
	glfwSetScrollCallback(window, Input::scrollCallback);
	b2Vec2 gravity(0.0f, -10.0f);
	world = new b2World(gravity);
	initialiseEntities();

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


	Menu::initialise(window);

	//for (int i = 0; i < 100000; i++) {
		Genome* a = new Genome(true);
		//Gene<int>* g = a->getGene<int>(GeneMarker::GM_SIZE, 0);
		Menu::focusGenome(a);
		//delete size;
	//}
}

void render() {
	de->render();
}

void update() {
	double currentTime = getTime();
	double elapsedTime = currentTime - lastTime;
	double deltaTime = elapsedTime * 0.001;
	lastTime = currentTime;
	deltaTime = 0.013;

	cam->update(deltaTime);
	de->update(deltaTime);
	world->Step(1.0f / 60.0f, 6, 2);

	if (Input::isDown(GLFW_KEY_E)) {
		//de->body->physicsBody->ApplyLinearImpulse(b2Vec2(0.0f, 100.0f), de->body->physicsBody->GetWorldCenter(), true);
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

	//IMGUI_CHECKVERSION();
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//ImGui::StyleColorsDark();

	//ImGui_ImplGlfw_InitForOpenGL(window, true);
	//ImGui_ImplOpenGL3_Init();
	bool showDemo = true;
	glfwSwapInterval(1);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//ImGui_ImplOpenGL3_NewFrame();
		//ImGui_ImplGlfw_NewFrame();
		//ImGui::NewFrame();

		//ImGui::ShowDemoWindow(&showDemo);

		update();
		render();

		Menu::renderUI();

		//ImGui::Render();
		//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	Menu::destroy();
	//ImGui_ImplOpenGL3_Shutdown();
	//ImGui_ImplGlfw_Shutdown();
	//ImGui::DestroyContext();
	return 0;
}