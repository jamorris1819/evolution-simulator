#pragma once
#include "glm/mat4x4.hpp"
#include "GL\glew.h"
#include "GLFW\glfw3.h"
#include "vertexarray.h"

namespace engine {
	class VertexArray;

	class VertexArrayObject {
	public:
		VertexArrayObject();
		VertexArrayObject(VertexArrayObject const& v);
		VertexArrayObject& operator=(VertexArrayObject const& v);
		virtual ~VertexArrayObject();
		void initialise();
		virtual void load();
		virtual void render();
		void unload();

		VertexArray const& getVertexArray() const { return vertexArray; }
		void setVertexArray(VertexArray const& vertexArray);
	protected:
		void bindVertexArray();
		void unbindVertexArray();
		VertexArray vertexArray;
		float* vertexData;
		GLuint vao[1];
		GLuint vbo[2];
		int vertexDataCount = 14;
		bool enabled;

		virtual void generateArrays();
		void generateVertexData();
		void allocateVertexMemory(int amount);
		void allocateIndexMemory(int amount);
		void setVertexData(float const* vertices);
		void setIndexData(unsigned short const* indices);
		virtual void assignAttributes();
	};
}