#include "pch.h"
#include "gamestatemanager.h"

namespace engine {
	void GameStateManager::addState(GameState* state) {
		std::unique_ptr<GameState> pointer(state);
		states.push(std::move(pointer));
	}

	void GameStateManager::popState() {
		states.pop();
	}

	GameState* GameStateManager::getState() {
		return states.top().get();
	}
}
