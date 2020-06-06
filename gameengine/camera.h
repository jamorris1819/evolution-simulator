#pragma once
#include "eventbus.h"
#include "events.h"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
#include "shader.h"

namespace engine {
	class Camera {
	public:
		Camera(EventBus& eb) : eventBus(eb), position(0, 0), targetPosition(0, 0), targetScale(1.0), scale(1.0), width(0),
			height(0), view(glm::mat4(1)), projection(glm::mat4(1)), viewport(glm::vec4()), ppm(64) {
			eventBus.subscribe(this, &Camera::handleMouseDrag);
			eventBus.subscribe(this, &Camera::handleMouseScroll);
		}
		void initialise(int w, int h);
		void setPosition(const glm::vec2 p) { position = p; }
		void update(double dt);
		void updateShader(const Shader& shad);
		glm::vec2 screenToWorldCoordinates(glm::vec2 screen);
		glm::vec2 screenToWorldCoordinates(float x, float y) {
			return screenToWorldCoordinates(glm::vec2(x, y));
		}
		const glm::vec2 getPosition() const { return position; }
	private:
		EventBus& eventBus;
		glm::vec2 position;
		glm::vec2 targetPosition;
		int ppm;
		int width;
		int height;
		double scale;
		double targetScale;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec4 viewport;

		void createProjection();
		void handleMouseDrag(MouseDragEvent* e);
		void handleMouseScroll(MouseScrollEvent* e);
	};
}