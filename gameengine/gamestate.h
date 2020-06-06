#pragma once
#include "eventbus.h"
#include "window.h"
#include "logger.h"

namespace engine {
	class GameState {
	public:
		GameState(Window* w, EventBus& eb) : eventBus(eb), window(w) {}
		virtual void initialise() = 0;
		virtual void load() = 0;
		virtual void update(double dt) = 0;
		virtual void render() = 0;
		virtual void unload() = 0;
	protected:
		EventBus& eventBus;
		Window* window;
	};
}