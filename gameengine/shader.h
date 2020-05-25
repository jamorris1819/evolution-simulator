#pragma once
#include <GL/glew.h>

namespace engine {
	class Shader {
	public:
		Shader(GLuint programId) : id(programId) {}
		GLuint getId() const { return id; }
	private:
		GLuint id;
	};
}