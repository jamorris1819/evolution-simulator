#pragma once
#include "glm/mat4x4.hpp"
#include "GL\glew.h"
#include "GLFW\glfw3.h"

namespace eng {
	class VertexArray;

	class VertexArrayObject {
	public:
		VertexArrayObject(VertexArray* polygonData);
		// todo: copy constructor
		~VertexArrayObject();
		void initialise();
		void load();
		void load(float* vertices, unsigned short* indices, int count);
		void render(glm::mat4 matrix);
		void unload();
		void setShader(GLuint shaderId);
		VertexArray const* getVertexArray() const { return polygonData; }
	private:
		void generateArrays();
		void allocateMemory(int amount);
		void process(const float* vertices, const unsigned short* indices, int count);
		void setVertexData(float const* vertices, int count);
		void setIndexData(unsigned short const* indices, int count);
		VertexArray* polygonData;
		GLuint shaderId;
		GLuint vao[1];
		GLuint vbo[2];
		int vertexDataCount;
		bool enabled;
		int dataSize;
		GLuint model;
	};
}