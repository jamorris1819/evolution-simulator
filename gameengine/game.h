#pragma once
#include "eventbus.h"
#include "window.h"
#include <string>
#include "gamestatemanager.h"

namespace engine {
	class Game {
	public:
		Game(std::string title);
		Game(const Game&) = delete;
		Game(const Game&&) = delete;
		void run();

	protected:
		Window* window;
		EventBus eventBus;
		GameStateManager stateManager;

		virtual void initialise() = 0;
		virtual void load() = 0;
		virtual void unload() = 0;

		void render() { stateManager.getState()->render(); }
		void update() { stateManager.getState()->update(); }

	private:
		void gameLoop() {
			while (window->isOpen()) {
				update();

				window->beginRender();
				render();
				window->endRender();
			}
		}
	};
}