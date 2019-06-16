#include "shaderutility.h"
#include <fstream>
#include "GLFW\glfw3.h"
#include <vector>

using namespace std;

ShaderUtility::ShaderUtility()
{
}


ShaderUtility::~ShaderUtility()
{
}

string ShaderUtility::readShader(char* filename)
{
	// Read in data from the given file.
	string shaderCode;
	ifstream file(filename, ios::in);

	if (!file.good())
	{
		cout << "Error reading file: " << filename << endl;
		terminate();
	}

	file.seekg(0, ios::end);
	shaderCode.resize((unsigned int)file.tellg());
	file.seekg(0, ios::beg);
	file.read(&shaderCode[0], shaderCode.size());
	file.close();

	return shaderCode;
}

GLuint ShaderUtility::createShader(GLenum shaderType, string source, char* shaderName)
{
	// Compile the shader from the source code.
	int compileResult = 0;
	GLuint shader = glCreateShader(shaderType);
	const char *shaderCodePtr = source.c_str();
	const int shaderCodeSize = source.size();

	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	if (compileResult == GL_FALSE)
	{
		int infoLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLength);
		vector<char> shaderLog(infoLength);
		glGetShaderInfoLog(shader, infoLength, nullptr, &shaderLog[0]);

		cout << "Error compiling shader: " << shaderName << endl;
		return 0;
	}

	return shader;
}

GLuint ShaderUtility::createProgram(char* vertexShaderFilename, char* fragmentShaderFilename)
{
	// Read in the shader data files.
	string vertexShaderData = readShader(vertexShaderFilename);
	string fragmentShaderData = readShader(fragmentShaderFilename);


	GLuint vertexShader = createShader(GL_VERTEX_SHADER, vertexShaderData, (char*)"Vertex Shader");
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentShaderData, (char*)"Fragment Shader");

	int linkResult = 0;

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

	if (linkResult == GL_FALSE)
	{
		int infoLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLength);
		vector<char> programLog(infoLength);
		glGetProgramInfoLog(program, infoLength, nullptr, &programLog[0]);
		cout << "Error linking shader: " << &programLog[0] << endl;
		return 0;
	}
	return program;
}