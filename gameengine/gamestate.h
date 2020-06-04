#pragma once
#include "eventbus.h"

namespace engine {
	class GameState {
	public:
		GameState(EventBus& eb) : eventBus(eb) {}
		virtual void initialise() = 0;
		virtual void load() = 0;
		virtual void update() = 0;
		virtual void render() = 0;
		virtual void unload() = 0;
	protected:
		EventBus& eventBus;
	};
}