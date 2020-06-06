#include "pch.h"
#include "game.h"

namespace engine {
	Game::Game(std::string title) {
		window = new Window(title, 1920, 1080);
		window->initialise();
		window->registerInputHandler(inputManager);
		InputManager::setEventBus(&eventBus);
	}

	void Game::run() {
		initialise();
		load();
		lastTime = getTime();

		gameLoop();

		unload();
	}
	void Game::gameLoop() {
		while (window->isOpen()) {
			double currentTime = getTime();
			double elapsedTime = currentTime - lastTime;
			elapsedTime *= 0.001;

			update(elapsedTime);

			window->beginRender();
			render();
			window->endRender();

			lastTime = currentTime;
		}
	}
}
