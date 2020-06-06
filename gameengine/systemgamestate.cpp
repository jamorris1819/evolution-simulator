#include "pch.h"
#include "systemgamestate.h"

namespace engine {
	void SystemGameState::initialise() {
		systemManager.addSystem(new RenderSystem(eventBus));

		camera.initialise(window->getWidth(), window->getHeight());
		eventBus.subscribe(this, &SystemGameState::handleMouseDrag);
		alignCamera();
	}

	void SystemGameState::update(double dt) {
		systemManager.update(entityManager.getEntities(), dt);
		camera.update(dt);
	}

	void SystemGameState::render() {
		systemManager.render(entityManager.getEntities());
	}

	void SystemGameState::alignCamera() {
		for (auto& shader : shaderManager.getShaders()) {
			camera.updateShader(shader.second);
		}
	}
}
