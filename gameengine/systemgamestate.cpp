#include "pch.h"
#include "systemgamestate.h"

namespace engine {
	void SystemGameState::initialise() {
		systemManager.addSystem(new RenderSystem(eventBus));

		camera.initialise(window->getWidth(), window->getHeight());
		for (auto& shader : shaderManager.getShaders()) {
			camera.updateShader(shader.second);
		}
	}

	void SystemGameState::update() {
		systemManager.update(entityManager.getEntities());
	}

	void SystemGameState::render() {
		systemManager.render(entityManager.getEntities());
	}
}
