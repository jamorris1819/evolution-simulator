#include <iostream>
#include "util\shaderutility.h"
#include <GLFW/glfw3.h>

using namespace std;

GLuint program;

void initialise()
{
	cout << glewInit() << endl;
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	ShaderUtility shaderUtility;
	program = shaderUtility.createProgram((char*)"src/Shaders/vertexshader.glsl", (char*)"src/Shaders/fragmentshader.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);
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

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}