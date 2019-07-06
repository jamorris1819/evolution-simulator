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
	this->width = width;
	this->height = height;

	ppm = 64; // Pixels per metre.

	projection = glm::ortho(
		0.0f,		// Left
		width / ppm,		// Right
		0.0f,		// Bottom
		height / ppm,		// Top
		-1.0f,		// Near
		1.0f		// Far
	);
	moveSpeed = speed;
	zoom = 1.0f;

	minZoom = 0.2f;
	maxZoom = 2.0f;

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

bool Camera::handleMovement(double deltaTime)
{
	bool alignmentNeeded = false;
	float zoomMoveSpeed = moveSpeed / zoom;

	if (Input::isDown(GLFW_KEY_D)) {
		this->position.x -= deltaTime * zoomMoveSpeed;
		alignmentNeeded = true;
	}

	if (Input::isDown(GLFW_KEY_A)) {
		this->position.x += deltaTime * zoomMoveSpeed;
		alignmentNeeded = true;
	}

	if (Input::isDown(GLFW_KEY_W)) {
		this->position.y -= deltaTime * zoomMoveSpeed;
		alignmentNeeded = true;
	}

	if (Input::isDown(GLFW_KEY_S)) {
		this->position.y += deltaTime * zoomMoveSpeed;
		alignmentNeeded = true;
	}

	return alignmentNeeded;
}

bool Camera::handleZoom(double deltaTime)
{
	if (Input::scrollUp()) zoom *= 1.1f;
	else if (Input::scrollDown()) zoom *= 0.9f;
	else return false;

	// Lock the zoom to the camera's limits.
	zoom = glm::clamp(zoom, minZoom, maxZoom);

	// Calculate the new viewport size.
	float zoomWidth = width / zoom;
	float zoomHeight = (height / width) * zoomWidth;

	// Create the new projection.
	projection = glm::ortho(
		(width - zoomWidth) / ppm,		// Left
		zoomWidth / ppm,				// Right
		(height - zoomHeight) / ppm,	// Bottom
		zoomHeight / ppm,				// Top
		-1.0f,					// Near
		1.0f					// Far
	);

	return true;
}

void Camera::update(double deltaTime)
{
	bool alignmentNeeded = false;
	alignmentNeeded = handleMovement(deltaTime) || alignmentNeeded;
	alignmentNeeded = handleZoom(deltaTime) || alignmentNeeded;
	
	// If a change has been made to the viewport, send these changes to the shader.
	if(alignmentNeeded) align();
}