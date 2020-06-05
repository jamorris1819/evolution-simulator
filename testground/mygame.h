#pragma once
#include "game.h"
#include <iostream>
#include "events.h"
#include "mylevel.h"

class MyGame : public engine::Game {
public:
	MyGame() : Game("My Game") {
		level = new MyLevel(window, eventBus);
		stateManager.addState(level);
	}
	virtual void initialise() override { level->initialise(); };
	virtual void load() override { level->load(); };
	virtual void unload() override { level->unload(); };
private:
	MyLevel* level;
};