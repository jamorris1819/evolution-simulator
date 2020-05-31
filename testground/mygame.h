#pragma once
#include "game.h"
#include <iostream>

using namespace std;

class MyGame : public engine::Game {
public:
	MyGame() : Game("My Game") {}
	virtual void initialise() override { cout << "init" << endl; };
	virtual void load() override { cout << "load" << endl; };
	virtual void unload() override { cout << "unload" << endl; };

	virtual void render() override { cout << "render" << endl; };
	virtual void update() override { cout << "update" << endl; };
};