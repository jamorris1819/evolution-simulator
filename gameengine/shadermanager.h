#pragma once
#include "shader.h"
#include <unordered_map>
#include <GL/glew.h>
#include <fstream>
#include <string>

namespace engine {
	class ShaderManager {
	public:
		const Shader& getShader(std::string);
		const Shader& addShader(std::string, char*, char*);
	private:
		std::unordered_map<std::string, Shader> shaders;
		std::string readShader(char*);
		GLuint compileShaderProgram(GLenum, std::string, char*);
		GLuint createShader(std::string, char*, char*);
	};
}