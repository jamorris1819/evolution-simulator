#include "pch.h"
#include "polygon.h"

eng::VertexRenderer::VertexRenderer(GLuint shaderID) {
	this->shaderID = shaderID;
	overrideColour = glm::vec3(1, 0, 1);	// magenta so it's obvious this hasn't been set.
	useOverrideColour = false;
	vao = nullptr;
	visible = true;
}

eng::VertexRenderer::~VertexRenderer() {
	delete vao;
}

void eng::VertexRenderer::render(glm::mat4 matrix) {
	if (!visible) return;
	glUseProgram(shaderID);

	// Tell fragment shader if we're overriding the colour.
	int useOverrideColourLocation = glGetUniformLocation(shaderID, "uOverrideEnabled");
	glUniform1i(useOverrideColourLocation, useOverrideColour);

	if (useOverrideColour) setColour();
	vao->render(matrix);
}

void eng::VertexRenderer::enableOverrideColour(glm::vec3 overrideColour) {
	useOverrideColour = true;
	this->overrideColour = overrideColour;
}

// Tell the shader what colour to use for the override.
void eng::VertexRenderer::setColour() {
	glUseProgram(shaderID);
	int overrideColourLocation = glGetUniformLocation(shaderID, "uOverrideColour");
	glUniform4f(overrideColourLocation, overrideColour.x, overrideColour.y, overrideColour.z, 1.0f);
}

void eng::VertexRenderer::load() {
	vao = new VertexArrayObject(this);
	vao->initialise();
	vao->setShader(shaderID);
	vao->load();
}

void eng::VertexRenderer::unload() {
	vao->unload();
}