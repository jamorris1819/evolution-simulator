#include "pch.h"
#include "shadermanager.h"
#include <ios>
#include <iostream>

namespace engine {

	GLuint ShaderManager::createShader(std::string name, char* vertexLocation, char* fragmentLocation) {
		std::string vertexShaderData = readShader(vertexLocation);
		std::string fragmentShaderData = readShader(fragmentLocation);

		GLuint vertexShader = compileShaderProgram(GL_VERTEX_SHADER, vertexShaderData, (char*)"Vertex Shader");
		GLuint fragmentShader = compileShaderProgram(GL_FRAGMENT_SHADER, fragmentShaderData, (char*)"Fragment Shader");
		int linkResult = 0;

		GLuint program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		glLinkProgram(program);
		glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

		if (linkResult == GL_FALSE) {
			int infoLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
			std::vector<char> programLog(infoLength);
			glGetProgramInfoLog(program, infoLength, nullptr, &programLog[0]);
			std::cout << "Error linking shader: " << &programLog[0] << std::endl;
			return 0;
		}
		return program;

	}

	const Shader& ShaderManager::getShader(std::string name) {
		auto search = shaders.find(name);

		if (search == shaders.end()) {
			throw std::exception("shader not found");
		}

		return search->second;
	}

	const Shader& ShaderManager::addShader(std::string name, char* vertexLocation, char* fragmentLocation) {
		GLuint shaderId = createShader(name, vertexLocation, fragmentLocation);
		Shader shader(shaderId);

		shaders.insert({ name, shader });

		return getShader(name);
	}

	std::string ShaderManager::readShader(char* filename) {
		// Read in data from the given file.
		std::string shaderCode;
		std::ifstream file(filename, std::ios::in);

		if (!file.good()) {
			std::cout << "Error reading file: " << filename << std::endl;
			terminate();
		}

		file.seekg(0, std::ios::end);
		shaderCode.resize((unsigned int)file.tellg());
		file.seekg(0, std::ios::beg);
		file.read(&shaderCode[0], shaderCode.size());
		file.close();

		return shaderCode;
	}

	GLuint ShaderManager::compileShaderProgram(GLenum shaderType, std::string source, char* shaderName) {
		int compileResult = 0;
		GLuint shader = glCreateShader(shaderType);
		const char* shaderCodePtr = source.c_str();
		const int shaderCodeSize = source.size();

		glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
		glCompileShader(shader);
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

		if (compileResult == GL_FALSE) {
			int infoLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
			std::vector<char> shaderLog(infoLength);
			glGetShaderInfoLog(shader, infoLength, nullptr, &shaderLog[0]);

			std::cout << "Error compiling shader: " << shaderName << std::endl;
			return 0;
		}

		return shader;
	}
}