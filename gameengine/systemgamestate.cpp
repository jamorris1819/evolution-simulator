#include "pch.h"
#include "systemgamestate.h"

namespace engine {
	void SystemGameState::initialise() {
		systemManager.addSystem(new RenderSystem(eventBus));
	}

	void SystemGameState::update() {
		systemManager.update(entityManager.getEntities());
	}

	void SystemGameState::render() {
		systemManager.render(entityManager.getEntities());
	}
}
