#pragma once
#include <GL/glew.h>

namespace engine {
	class Shader {
	public:
		Shader(GLuint programId) : id(programId) {}
		GLuint getId() const { return id; }
		void bind() const { glUseProgram(id); }
	private:
		GLuint id;
	};
}