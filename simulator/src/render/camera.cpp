#include "Camera.h"
#include "glm/gtx/transform.hpp"
#include <glm/gtx/quaternion.hpp>
#include "../util/input.h"

Camera::Camera(glm::vec2 position, GLuint shaderID)
{
	this->position = position;
	this->shaderID = shaderID;
}

void Camera::initialise(float width, float height, float speed)
{
	projection = glm::ortho(
		0.0f,		// Left
		width,		// Right
		0.0f,		// Bottom
		height,		// Top
		-1.0f,		// Near
		1.0f		// Far
	);
	moveSpeed = speed;

	align();
}

void Camera::align()
{
	glUseProgram(shaderID);

	// Create the view matrix.
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(position, 0));
	view = translate;

	// Apply the camera transformation.
	int uView = glGetUniformLocation(shaderID, "uView");
	glUniformMatrix4fv(uView, 1, GL_TRUE, &view[0][0]);

	// Apply the projection.
	int uProjection = glGetUniformLocation(shaderID, "uProjection");
	glUniformMatrix4fv(uProjection, 1, GL_TRUE, &projection[0][0]);
}

void Camera::update(double deltaTime)
{
	bool alignmentNeeded = false;

	if (Input::isDown(GLFW_KEY_D)) {
		this->position.x -= deltaTime * moveSpeed;
		alignmentNeeded = true;
	}

	if (Input::isDown(GLFW_KEY_A)) {
		this->position.x += deltaTime * moveSpeed;
		alignmentNeeded = true;
	}

	if (Input::isDown(GLFW_KEY_W)) {
		this->position.y -= deltaTime * moveSpeed;
		alignmentNeeded = true;
	}

	if (Input::isDown(GLFW_KEY_S)) {
		this->position.y += deltaTime * moveSpeed;
		alignmentNeeded = true;
	}

	// If a change has been made to the viewport, send these changes to the shader.
	if(alignmentNeeded) align();
}