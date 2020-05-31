#include "pch.h"
#include "game.h"

namespace engine {
	Game::Game(std::string title) {
		window = new Window(title, 1920, 1080);
		window->initialise();
	}

	void Game::run() {
		initialise();
		load();

		gameLoop();

		unload();
	}
}
