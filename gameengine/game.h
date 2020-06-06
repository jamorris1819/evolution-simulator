#pragma once
#include "eventbus.h"
#include "inputmanager.h"
#include "window.h"
#include <string>
#include "gamestatemanager.h"
#include <chrono>

namespace engine {
	class Game {
	public:
		Game(std::string title);
		Game(const Game&) = delete;
		Game(const Game&&) = delete;
		void run();
		Window* window;

	protected:
		EventBus eventBus;
		InputManager inputManager;
		GameStateManager stateManager;

		virtual void initialise() = 0;
		virtual void load() = 0;
		virtual void unload() = 0;

		void render() { stateManager.getState()->render(); }
		void update(double dt) { stateManager.getState()->update(dt); }

	private:
		void gameLoop();
		long getTime() {
			return std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now().time_since_epoch()
				).count();
		}

		long lastTime;
	};
}