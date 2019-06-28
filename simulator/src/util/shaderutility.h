#pragma once
#include <string>
#include <GL\glew.h>
#include <iostream>

using namespace std;

class ShaderUtility
{
private:
	string readShader(char *filename);
	GLuint createShader(GLenum shaderType, string source, char* shaderName);
public:
	ShaderUtility();
	~ShaderUtility();
	GLuint createProgram(char* vertexShaderFilename, char* fragmentShaderFilename);
};

