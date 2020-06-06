#include "pch.h"
#include "camera.h"
#include "glm/gtx/transform.hpp"
#include <glm/gtx/quaternion.hpp>
#include <iostream>

namespace engine {
	void Camera::initialise(int w, int h) {
		width = w;
		height = h;
		scale = 1.0;

		createProjection();
	}

	void Camera::update(double dt) {
		scale = scale + (targetScale - scale) * dt * 10.0;
		position = position + (targetPosition - position) * glm::vec2(dt, dt) * glm::vec2(10.0, 10.0);
		eventBus.publish(new CameraEvent());
	}

	void Camera::updateShader(const Shader& shad) {
		glUseProgram(shad.getId());

		// Create the view matrix.
		glm::mat4 translate = glm::translate(glm::mat4(1.0f),
			glm::vec3(position, 0)
		);
		view = translate;

		// Apply the camera transformation.
		int uView = glGetUniformLocation(shad.getId(), "uView");
		glUniformMatrix4fv(uView, 1, GL_TRUE, &view[0][0]);

		createProjection();

		// Apply the projection.
		int uProjection = glGetUniformLocation(shad.getId(), "uProjection");
		glUniformMatrix4fv(uProjection, 1, GL_TRUE, &projection[0][0]);
	}

	glm::vec2 Camera::screenToWorldCoordinates(glm::vec2 screen) {
		glm::mat4 vp = projection;
		glm::mat4 inv = glm::inverse(vp);

		glm::vec3 vIn(
			(screen.x / (double)width) - 0.5,
			 -1 * ((screen.y / (double)height) - 0.5),
			1.0);
		
		glm::vec4 pos = glm::vec4(vIn, 1.0) * inv;

		pos.w = 1.0 / pos.w;

		pos.x *= pos.w;
		pos.y *= pos.w;
		pos.z *= pos.w;

		return glm::vec2(pos) - targetPosition;
	}

	void Camera::createProjection() {
		float zoomWidth = (float)width / scale;
		float zoomHeight = ((float)height / (float)width) * zoomWidth;

		// Create the new projection.
		float boundaryWidth = zoomWidth / ppm;
		float boundaryHeight = zoomHeight / ppm;

		projection = glm::ortho(
			-boundaryWidth / 2,
			boundaryWidth / 2,
			-boundaryHeight / 2,
			boundaryHeight / 2,
			-1.0f,
			1.0f
		);

		viewport = glm::vec4(
			(width - zoomWidth) / ppm,
			(height - zoomHeight) / ppm,
			zoomWidth / ppm,
			zoomHeight / ppm
		);
	}

	void Camera::handleMouseDrag(MouseDragEvent* e) {
		if (e->button != 1) return; // Check if this is right mouse button

		targetPosition.x += (e->dx / ppm) / scale;
		targetPosition.y -= (e->dy / ppm) / scale;
	}

	void Camera::handleMouseScroll(MouseScrollEvent* e) {
		double zoom = glm::exp(e->dy * 0.2);
		if (scale * zoom < 0.01) return;

		double dx = (width / 2.0) - e->data.x;
		double dy = (height / 2.0) - e->data.y;

		targetPosition.x -= (dx / (scale * zoom) - dx / scale) / ppm;
		targetPosition.y += (dy / (scale * zoom) - dy / scale) / ppm;

		targetScale *= zoom;
		createProjection();

		eventBus.publish(new CameraEvent());
	}
}