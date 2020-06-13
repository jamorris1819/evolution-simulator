#pragma once
#include <GL/glew.h>
#include <string>
#include "glm/mat4x4.hpp"
#include <unordered_map>

namespace engine {
	class Shader {
	public:
		Shader(GLuint programId) : id(programId) {}
		GLuint getId() const { return id; }
		void bind() const { glUseProgram(id); }
		int getUniformName(std::string name) const {
			auto it = uniforms.find(name);

			if (it == uniforms.end()) return -1;

			return uniforms.at(name);
		}
		void setUniformMat4(std::string name, glm::mat4 matrix) const {
			int id = getUniformName(name);
			if (id == -1) return;
			glUniformMatrix4fv(id, 1, GL_TRUE, &matrix[0][0]);
		}
		void addUniform(std::string name, int id) {
			uniforms.insert(std::pair<std::string, int>(name, id));
		}
	private:
		GLuint id;
		std::unordered_map<std::string, int> uniforms;
	};
}