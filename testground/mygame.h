#pragma once
#include "game.h"
#include <iostream>
#include "events.h"

using namespace std;

class MyGame : public engine::Game {
public:
	MyGame() : Game("My Game") {
		eventBus.subscribe(this, &MyGame::handleInputDown);
		eventBus.subscribe(this, &MyGame::handleInputUp);
		eventBus.subscribe(this, &MyGame::handleInputHold);
		eventBus.subscribe(this, &MyGame::handleMouseDown);
		eventBus.subscribe(this, &MyGame::handleMouseUp);
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

	void handleMouseDown(engine::MouseButtonDownEvent* k) {
		std::cout << "Mouse button down: " << k->button << " at (" << k->data.x << ", " << k->data.y << ")" << std::endl;
	}

	void handleMouseUp(engine::MouseButtonUpEvent* k) {
		std::cout << "Mouse button up: " << k->button << " at (" << k->data.x << ", " << k->data.y << ")" << std::endl;
	}
};