#pragma once
#include "gamestate.h"
#include <iostream>
#include "eventbus.h"
#include "events.h"

class MyLevel : public engine::GameState {
public:
	MyLevel(engine::EventBus& eb) : GameState(eb) {
		std::cout << "level constructed" << std::endl;
		eventBus.subscribe(this, &MyLevel::handleInputDown);
		eventBus.subscribe(this, &MyLevel::handleInputUp);
		eventBus.subscribe(this, &MyLevel::handleInputHold);
		eventBus.subscribe(this, &MyLevel::handleMouseDown);
		eventBus.subscribe(this, &MyLevel::handleMouseUp);
		eventBus.subscribe(this, &MyLevel::handleMouseDrag);
		eventBus.subscribe(this, &MyLevel::handleMouseScroll);
	}
	virtual void initialise() override { std::cout << "initialise" << std::endl; }
	virtual void load() override { std::cout << "load" << std::endl; }
	virtual void render() override { std::cout << "render" << std::endl; }
	virtual void update() override { }
	virtual void unload() override { }

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

	void handleMouseDrag(engine::MouseDragEvent* k) {
		std::cout << "Mouse drag (" << k->button << ") [" << k->dx << ", " << k->dy << "]" << std::endl;
	}

	void handleMouseScroll(engine::MouseScrollEvent* k) {
		std::cout << "Mouse scroll [" << k->dx << ", " << k->dy << "]" << std::endl;
	}
};