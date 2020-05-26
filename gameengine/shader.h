#pragma once
#include <GL/glew.h>
#include <string>
#include "glm/mat4x4.hpp"

namespace engine {
	class Shader {
	public:
		Shader(GLuint programId) : id(programId) {}
		GLuint getId() const { return id; }
		void bind() const { glUseProgram(id); }
		int getUniformName(std::string name) { return glGetUniformLocation(id, name.c_str()); }
		void setUniformMat4(std::string name, glm::mat4 matrix) {
			int id = getUniformName(name);
			if (id == -1) return;
			glUniformMatrix4fv(id, 1, GL_TRUE, &matrix[0][0]);
		}
	private:
		GLuint id;
	};
}