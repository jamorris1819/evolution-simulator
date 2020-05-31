#pragma once
#include "gamestate.h"
#include <iostream>

class MyLevel : public engine::GameState {
public:
	MyLevel() { std::cout << "level constructed" << std::endl; }
	virtual void initialise() override { std::cout << "initialise" << std::endl; }
	virtual void load() override { std::cout << "load" << std::endl; }
	virtual void render() override { std::cout << "render" << std::endl; }
	virtual void update() override { std::cout << "update" << std::endl; }
	virtual void unload() override { std::cout << "unload" << std::endl; }
};