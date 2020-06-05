#include "pch.h"
#include "camera.h"
#include "glm/gtx/transform.hpp"
#include <glm/gtx/quaternion.hpp>

namespace engine {
	void Camera::initialise(int w, int h) {
		width = w;
		height = h;
		zoom = 1.0;

		createProjection();
	}

	void Camera::update() {
		if (targetPosition == position) return;

		position = position + (targetPosition - position) * glm::vec2(0.25, 0.25);
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

		// Apply the projection.
		int uProjection = glGetUniformLocation(shad.getId(), "uProjection");
		glUniformMatrix4fv(uProjection, 1, GL_TRUE, &projection[0][0]);
	}

	void Camera::createProjection() {
		float zoomWidth = (float)width / zoom;
		float zoomHeight = ((float)height / (float)width) * zoomWidth;

		float ppm = 1;

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
		if (e->button != 1) return; // Check if this is right button

		targetPosition.x += e->dx;
		targetPosition.y -= e->dy;
	}
}