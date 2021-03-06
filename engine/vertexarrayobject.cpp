#include "pch.h"
#include "vertexarrayobject.h"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "glm\gtc\matrix_transform.hpp"

namespace eng {
	VertexArrayObject::VertexArrayObject() {
		enabled = false;
		vao[0] = 0;
		model = -1;

		vbo[0] = 0;
		vbo[1] = 0;
		vbo[2] = 0;

		vertexData = nullptr;
		shaderId = 0;
	}

	VertexArrayObject::~VertexArrayObject() {
		if (vertexData != nullptr) {
			delete[] vertexData;
		}
	}

	VertexArrayObject::VertexArrayObject(VertexArrayObject const& v) {
		int vertexDataSize = v.vertexArray.getVertexCount() * vertexDataCount;
		vertexData = new float[vertexDataSize];
		for (int i = 0; i < vertexDataSize; ++i)
			vertexData[i] = v.vertexData[i];

		vertexArray = v.vertexArray;
		shaderId = v.shaderId;

		vao[0] = v.vao[0];
		vbo[0] = v.vbo[0];
		vbo[1] = v.vbo[1];

		enabled = v.enabled;
		model = v.model;
	}

	VertexArrayObject& VertexArrayObject::operator=(VertexArrayObject const& v) {
		int vertexDataSize = v.vertexArray.getVertexCount() * vertexDataCount;
		float* newData = new float[vertexDataSize];
		for (int i = 0; i < vertexDataSize; ++i)
			newData[i] = v.vertexData[i];
		delete[] vertexData;

		vertexArray = v.vertexArray;
		shaderId = v.shaderId;

		vao[0] = v.vao[0];
		vbo[0] = v.vbo[0];
		vbo[1] = v.vbo[1];

		enabled = v.enabled;
		model = v.model;
		model = v.model;

		return *this;
	}

	void VertexArrayObject::generateArrays() {
		glGenVertexArrays(1, vao);
		glBindVertexArray(vao[0]);
		glGenBuffers(2, vbo);
	}

	void VertexArrayObject::setVertexArray(VertexArray const& vertexArray) {
		this->vertexArray = vertexArray;
	}

	void VertexArrayObject::generateVertexData() {
		if (vertexData != nullptr) {
			delete[] vertexData;
		}

		// Put all vertex information into one large array, ready for use by OpenGL.
		int numOfVertices = vertexArray.getVertexCount();

		vertexData = new float[vertexDataCount * numOfVertices];

		for (int i = 0; i < numOfVertices; i++) {
			int offset = vertexDataCount * i;

			Vertex v = vertexArray.getVertices()[i];

			vertexData[offset] = v.getPosition().x;
			vertexData[offset + 1] = v.getPosition().y;
			vertexData[offset + 2] = v.getColour().x;
			vertexData[offset + 3] = v.getColour().y;
			vertexData[offset + 4] = v.getColour().z;
		}
	}

	void VertexArrayObject::setShader(GLuint shaderId) {
		this->shaderId = shaderId;
	}

	void VertexArrayObject::allocateVertexMemory(int amount) {
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, amount * vertexDataCount * sizeof(float), nullptr, GL_STATIC_DRAW);
	}

	void VertexArrayObject::allocateIndexMemory(int amount) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, amount * sizeof(unsigned short), nullptr, GL_STATIC_DRAW);
	}

	void VertexArrayObject::initialise() {
		generateArrays();
	}

	void VertexArrayObject::bindVertexArray() {
		glBindVertexArray(vao[0]);
	}

	void VertexArrayObject::unbindVertexArray() {
		glBindVertexArray(0);
	}

	void VertexArrayObject::load() {
		bindVertexArray();

		generateVertexData();

		allocateVertexMemory(vertexArray.getVertexCount());
		allocateIndexMemory(vertexArray.getIndexCount());

		setVertexData(vertexData);
		setIndexData(vertexArray.getIndices().data());

		assignAttributes();

		unbindVertexArray();
		enabled = true;
	}

	void VertexArrayObject::assignAttributes() {
		int vPositionLocation = glGetAttribLocation(shaderId, "vPosition");
		int vColourLocation = glGetAttribLocation(shaderId, "vColour");

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

		glEnableVertexAttribArray(vPositionLocation);
		glVertexAttribPointer(vPositionLocation, 2, GL_FLOAT, false, vertexDataCount * sizeof(float), nullptr);

		glEnableVertexAttribArray(vColourLocation);
		glVertexAttribPointer(vColourLocation, 3, GL_FLOAT, false, vertexDataCount * sizeof(float), (const GLvoid*)(2 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VertexArrayObject::setVertexData(float const* vertices) {
		int count = vertexArray.getVertexCount();
		count *= vertexDataCount;		// There are 5 attributes for every vertex.
		GLint* size = new GLint;

		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferSubData(GL_ARRAY_BUFFER, NULL, count * sizeof(float), (const GLvoid*)vertices);

		glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, size);

		if (count * sizeof(float) != *size) {
			std::cout << "Vertex data not loaded onto graphics card correctly" << std::endl;
			terminate();
		}

		delete size;
	}

	void VertexArrayObject::setIndexData(unsigned short const* indices) {
		int count = vertexArray.getIndexCount();
		GLint* size = new GLint;
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, NULL, count * sizeof(unsigned short), (const GLvoid*)indices);

		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, size);

		if (count * sizeof(short) != *size) {
			std::cout << "Index data not loaded onto graphics card correctly" << std::endl;
			terminate();
		}

		delete size;
	}

	void VertexArrayObject::render(glm::mat4 matrix) {
		if (!enabled)
			return;

		// Attach model matrix to shader.
		if (model == -1) model = glGetUniformLocation(shaderId, "uModel");
		glUniformMatrix4fv(model, 1, GL_TRUE, &matrix[0][0]);

		// Bind vertex and render polygon.
		glBindVertexArray(vao[0]);
		glDrawElements(GL_TRIANGLES, vertexArray.getIndexCount(), GL_UNSIGNED_SHORT, 0);
		glBindVertexArray(0);
	}

	void VertexArrayObject::unload() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
		glDeleteBuffers(2, vbo);
		glDeleteVertexArrays(1, vao);
	}
}