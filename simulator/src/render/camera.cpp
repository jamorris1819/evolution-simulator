#include "Camera.h"
#include "glm/gtx/transform.hpp"
#include <glm/gtx/quaternion.hpp>

Camera::Camera(glm::vec2 position, GLuint shaderID)
{
	this->position = position;
	this->shaderID = shaderID;
}

void Camera::initialise()
{
	align();
}

void Camera::align()
{
	glUseProgram(shaderID);

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0));
	view = translate;

	// Apply the camera transformation.
	int uView = glGetUniformLocation(shaderID, "uView");
	glUniformMatrix4fv(uView, 1, GL_TRUE, &view[0][0]);

	// Create + apply the orthographic projection.
	glm::mat4 orthoProjection = glm::ortho(
		0.0f,		// Left
		640.0f,		// Right
		0.0f,		// Bottom
		480.0f,		// Top
		-1.0f,		// Near
		1.0f		// Far
	);
	int uProjection = glGetUniformLocation(shaderID, "uProjection");

	glUniformMatrix4fv(uProjection, 1, GL_TRUE, &orthoProjection[0][0]);
}

void Camera::update(double deltaTime)
{
	align();
}