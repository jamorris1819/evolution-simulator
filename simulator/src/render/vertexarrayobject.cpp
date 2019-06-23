#include "vertexarrayobject.h"
#include "polygonData.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "glm\gtc\matrix_transform.hpp"



VertexArrayObject::VertexArrayObject(PolygonData* polygonData)
{
	enabled = false;

	if (polygonData == nullptr)
		return;

	this->polygonData = polygonData;
	vao[0] = 0;
	enabled = true;
}


VertexArrayObject::~VertexArrayObject()
{
	// Polygon Data is deleted by the Polygon class at the same time as this being called.
}

void VertexArrayObject::initialise()
{
	enabled = false;
	vertexDataCount = 5;
	generateArrays();
}

void VertexArrayObject::generateArrays()
{
	glGenVertexArrays(1, vao);
	glBindVertexArray(vao[0]);
	glGenBuffers(2, vbo);
}

void VertexArrayObject::setShader(GLuint shaderId)
{
	this->shaderId = shaderId;
}

void VertexArrayObject::allocateMemory(int amount)
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, amount * vertexDataCount * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, amount * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
}

void VertexArrayObject::load()
{
	process(polygonData->getVertices(), polygonData->getIndices().data(), polygonData->getVertexCount());
}

void VertexArrayObject::load(float* vertices, float* indices, int count)
{
	process(vertices, indices, count);
}

void VertexArrayObject::process(float* vertices, float* indices, int count)
{
	glBindVertexArray(vao[0]);

	dataSize = count;

	this->allocateMemory(dataSize);

	setVertexData(vertices, dataSize);
	setIndexData(indices, dataSize);

	int vPositionLocation = glGetAttribLocation(shaderId, "vPosition");
	int vColourLocation = glGetAttribLocation(shaderId, "vColour");

	glEnableVertexAttribArray(vPositionLocation);
	glVertexAttribPointer(vPositionLocation, 2, GL_FLOAT, false, vertexDataCount * sizeof(float), nullptr);

	glEnableVertexAttribArray(vColourLocation);
	glVertexAttribPointer(vColourLocation, 3, GL_FLOAT, false, vertexDataCount * sizeof(float), (const GLvoid*)(2 * sizeof(float)));

	glBindVertexArray(0);
	enabled = true;
}

void VertexArrayObject::setVertexData(float* vertices, int count)
{
	count *= vertexDataCount;		// There are 5 attributes for every vertex.
	GLint* size = new GLint;

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBufferSubData(GL_ARRAY_BUFFER, NULL, count * sizeof(float), (const GLvoid*)vertices);

	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, size);

	if (count * sizeof(float) != *size)
	{
		std::cout << "Vertex data not loaded onto graphics card correctly" << std::endl;
		terminate();
	}

	delete size;
}

void VertexArrayObject::setIndexData(float* indices, int count)
{
	GLint* size = new GLint;
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, NULL, count * sizeof(float), (const GLvoid*)indices);

	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, size);

	if (count * sizeof(float) != *size)
	{
		std::cout << "Index data not loaded onto graphics card correctly" << std::endl;
		terminate();
	}

	delete size;
}

void VertexArrayObject::render(glm::mat4 matrix)
{
	if (!enabled)
		return;

	// Attach model matrix to shader.
	GLuint uModel = glGetUniformLocation(shaderId, "uModel");
	glUniformMatrix4fv(uModel, 1, GL_TRUE, &matrix[0][0]);

	// Bind vertex and render polygon.
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_POLYGON, 0, dataSize);
	glBindVertexArray(0);
}

void VertexArrayObject::unload()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glDeleteBuffers(2, vbo);
	glDeleteVertexArrays(1, vao);
}
