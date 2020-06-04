#pragma once
#include "eventbus.h"
#include "inputmanager.h"
#include "window.h"
#include <string>

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
		InputManager inputManager;

		virtual void initialise() = 0;
		virtual void load() = 0;
		virtual void unload() = 0;

		virtual void render() = 0;
		virtual void update() = 0;

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