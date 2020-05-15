#pragma once
#include "glm/mat4x4.hpp"
#include "GL\glew.h"
#include "GLFW\glfw3.h"

class PolygonData;

class VertexArrayObject
{
public:
	VertexArrayObject(PolygonData* polygonData);
	~VertexArrayObject();
	void initialise();
	void load();
	void load(float* vertices, float* indices, int count);
	void render(glm::mat4 matrix);
	void unload();
	void setShader(GLuint shaderId);
	PolygonData* polygonData;
private:
	void generateArrays();
	void allocateMemory(int amount);
	void process(float* vertices, float* indices, int count);
	void setVertexData(float* vertices, int count);
	void setIndexData(float* indices, int count);
	GLuint shaderId;
	GLuint vao[1];
	GLuint vbo[2];
	float* currentAccessV;
	float* currentAccessI;
	int vertexDataCount;
	bool enabled;
	int dataSize;
	GLuint model;
};

