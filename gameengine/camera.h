#pragma once
#include "eventbus.h"
#include "events.h"
#include "glm/vec2.hpp"
#include "glm/mat4x4.hpp"
#include "shader.h"

namespace engine {
	class Camera {
	public:
		Camera(EventBus& eb) : eventBus(eb), position(glm::vec2(0, 0)), zoom(1.0), width(0),
			height(0), view(glm::mat4(1)), projection(glm::mat4(1)), viewport(glm::vec4()) {}
		void initialise(int w, int h);
		void setPosition(const glm::vec2 p) { position = p; }
		//void update(double dt);
		void updateShader(const Shader& shad);
		const glm::vec2 getPosition() const { return position; }
	private:
		EventBus& eventBus;
		glm::vec2 position;
		int width;
		int height;
		double zoom;
		glm::mat4 view;
		glm::mat4 projection;
		glm::vec4 viewport;

		void createProjection();
	};
}