#pragma once
#include <memory>
#include <stack>
#include "gamestate.h"


namespace engine {
	class GameStateManager {
	public:
		GameStateManager() {};
		void addState(GameState* state);
		void popState();
		GameState* getState();

	private:
		std::stack<std::unique_ptr<GameState>> states;
	};
}