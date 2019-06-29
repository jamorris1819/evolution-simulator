#include <iostream>
#include "util\shaderutility.h"
#include <vector>
#include "render\vertex.h"
#include "render\polygondata.h"
#include "render\polygon.h"
#include "render\vertexarrayobject.h"
#include "entities\drawnentity.h"
#include "render\camera.h"
#include "util\input.h"

#include "render\ui\menu.h"
#include "genetics\gene.h"
#include "genetics\genotype.h"
#include "genetics\genemarker.h"

using namespace std;

GLuint program;
GLFWwindow* window;
float lastTime;
float width = 1920.0f;
float height = 1080.0f;

DrawnEntity* de;
Camera* cam;

void initialiseEntities() {
	vector<Vertex> vertices;
	Vertex v(-50.0f, 50.0f);
	v.setColour(glm::vec3(0, 0, 1));
	vertices.push_back(v);
	vertices.push_back(Vertex(-50.0f, -50.0f));
	vertices.push_back(Vertex(50.0f, -50.0f));
	vertices.push_back(Vertex(50.0f, 50.0f));

	PolygonR* pol;
	pol = new PolygonR(program);
	pol->setVertices(vertices);
	pol->load();

	de = new DrawnEntity(glm::vec3(200, 200, 0));
	de->setPolygon(pol);

	cam = new Camera(glm::vec2(0, 0), program);
	cam->initialise(width, height, 100.0f);

	std::cout << ToString(GeneMarker::GM_COLOUR_R) << std::endl;
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
	initialiseEntities();

	Menu::initialise(window);

	for (int i = 0; i < 100000; i++) {
		Genotype* a = new Genotype(true);
		//Gene<int>* g = a->getGene<int>(GeneMarker::GM_SIZE, 0);
		delete a;
		//delete size;
	}
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