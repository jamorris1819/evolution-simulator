#pragma once
#include "glm/mat4x4.hpp"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "vertexarray.h"

namespace eng {
	class VertexArray;

	class VertexArrayObject {
	public:
		VertexArrayObject();
		VertexArrayObject(VertexArrayObject const& v);
		VertexArrayObject& operator=(VertexArrayObject const& v);
		virtual ~VertexArrayObject();
		void initialise();
		virtual void load();
		virtual void render(glm::mat4 matrix);
		void unload();
		void setShader(GLuint shaderId);

		VertexArray const& getVertexArray() const { return vertexArray; }
		void setVertexArray(VertexArray const& vertexArray);
	protected:
		void bindVertexArray();
		void unbindVertexArray();
		VertexArray vertexArray;
		float* vertexData;
		GLuint shaderId;
		GLuint vao[1];
		GLuint vbo[4];
		int vertexDataCount = 5;
		bool enabled;
		GLuint model;

		virtual void generateArrays();
		void generateVertexData();
		void allocateVertexMemory(int amount);
		void allocateIndexMemory(int amount);
		void setVertexData(float const* vertices);
		void setIndexData(unsigned short const* indices);
		virtual void assignAttributes();
	};
}