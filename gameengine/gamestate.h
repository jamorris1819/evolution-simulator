#pragma once

namespace engine {
	class GameState {
	public:
		virtual void initialise() = 0;
		virtual void load() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void unload() = 0;
	};
}