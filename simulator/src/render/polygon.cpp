#include "polygon.h"

PolygonR::PolygonR(GLuint shaderID)
{
	this->shaderID = shaderID;
}

PolygonR::~PolygonR()
{
	delete vao;
}

void PolygonR::render(glm::mat4 matrix)
{
	glUseProgram(shaderID);
	vao->render(matrix);
}

void PolygonR::load()
{
	vao = new VertexArrayObject(this);
	vao->initialise();
	vao->setShader(shaderID);
	vao->load();
}

void PolygonR::unload()
{
	vao->unload();
}