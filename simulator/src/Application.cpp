#include <iostream>
#include "util\shaderutility.h"
#include <GLFW/glfw3.h>
#include <vector>
#include "render\vertex.h"
#include "render\polygondata.h"
#include "render\polygon.h"
#include "render\vertexarrayobject.h"
#include "entities\drawnentity.h"
#include "render\camera.h"

using namespace std;

GLuint program;

DrawnEntity* de;
Camera* cam;

void initialiseEntites() {
	vector<Vertex> vertices;
	vertices.push_back(Vertex(-50.0f, 50.0f));
	vertices.push_back(Vertex(-50.0f, -50.0f));
	vertices.push_back(Vertex(50.0f, -50.0f));
	vertices.push_back(Vertex(50.0f, 50.0f));

	PolygonR* pol;
	pol = new PolygonR(program);
	pol->setVertices(vertices);
	pol->load();

	de = new DrawnEntity(glm::vec3(200, 200, 0));
	de->setPolygon(pol);
	de->setVelocity(glm::vec3(1, 0, 0));

	cam = new Camera(glm::vec2(0, 0), program);
	cam->initialise();
}

void initialise()
{
	cout << glewInit() << endl;
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	glViewport(0, 0, 640, 480);

	ShaderUtility shaderUtility;
	program = shaderUtility.createProgram((char*)"src/Shaders/vertexshader.glsl", (char*)"src/Shaders/fragmentshader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_POLYGON);
	

	initialiseEntites();
}

void render() {
	de->render();
}

void update() {
	// TODO: Add deltatime
	de->update(0.1f);
}

int main(int argc, char **argv)
{
	GLFWwindow* window;
	glutInit(&argc, argv);

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Evolution Simulator", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	initialise();

	glUseProgram(program);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		update();
		render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);
		

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}