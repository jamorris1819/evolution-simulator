// testground.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "entity.h"
#include "positioncomponent.h"
#include "systemmanager.h"
#include "entitymanager.h"
#include "shadermanager.h"
#include "vertexarray.h"

void initialise()
{
	engine::EntityManager entityManager;
	auto entity = new engine::Entity("test");
	entity->addComponent(new engine::PositionComponent(glm::vec2(100, 20)));
	entityManager.addEntity(entity);
	engine::SystemManager manager;
	manager.update(entityManager.getEntities());

	engine::ShaderManager sm;
	const engine::Shader& myShader = sm.addShader("basic", (char*)"shaders/vertexshader.glsl", (char*)"shaders/fragmentshader.glsl");

	engine::VertexArray va1;
	engine::Vertex v1(0, 0);
	va1.setVertices(std::vector<engine::Vertex>{v1});

	engine::VertexArray va2;
	engine::Vertex v2(1, 1);
	va2.setVertices(std::vector<engine::Vertex>{v2});

	engine::VertexArray va3 = va1 + va2;
	va3 += va1;

	int a = 3;
}

void error_callback(int error, const char* description) {
	fprintf(stderr, "Error: %s\n", description);
}


GLFWwindow* window;

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
int main() {
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwSetErrorCallback(error_callback);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1920, 1080, "Evolution Simulator", NULL, NULL);
	//glfwSetWindowSizeCallback(window, window_size_callback);
	glfwSetWindowPos(window, (3440.0f - 1920) / 2, (1440.0f - 1080) / 2);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glewInit();

	initialise();

	bool showDemo = true;
	glfwSwapInterval(1);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window)) {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//update();
		//render();

		//menu->render();

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	//menu->unload();
	return 0;
}