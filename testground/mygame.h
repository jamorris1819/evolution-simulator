#pragma once
#include "game.h"
#include <iostream>
#include "keydownevent.h"
#include "keyupevent.h"
#include "keyholdevent.h"

using namespace std;

class MyGame : public engine::Game {
public:
	MyGame() : Game("My Game") {
		eventBus.subscribe(this, &MyGame::handleInputDown);
		eventBus.subscribe(this, &MyGame::handleInputUp);
		eventBus.subscribe(this, &MyGame::handleInputHold);
	}
	virtual void initialise() override { cout << "init" << endl; };
	virtual void load() override { cout << "load" << endl; };
	virtual void unload() override { cout << "unload" << endl; };

	virtual void render() override { };
	virtual void update() override { };

	void handleInputDown(engine::KeyDownEvent* k) {
		std::cout << "Key pressed: " << k->key << std::endl;
	}

	void handleInputUp(engine::KeyUpEvent* k) {
		std::cout << "Key released: " << k->key << std::endl;
	}

	void handleInputHold(engine::KeyHoldEvent* k) {
		std::cout << "Key held: " << k->key << std::endl;
	}
};