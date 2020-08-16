#pragma once
#include "systemgamestate.h"
#include <iostream>
#include "eventbus.h"
#include "events.h"
#include "rendercomponent.h"
#include "positioncomponent.h"
#include "rectangle.h"
#include "triangle.h"
#include "logger.h"
#include "worldtile.h"
#include <sstream>
#include "terraingenerator.h"

class MyLevel : public engine::SystemGameState {
public:
	engine::TerrainGenerator* terrainGenerator;
	MyLevel(engine::Window* w, engine::EventBus& eb) : SystemGameState(w, eb) {
		std::cout << "level constructed" << std::endl;
		eventBus.subscribe(this, &MyLevel::handleInputDown);
		eventBus.subscribe(this, &MyLevel::handleInputUp);
		eventBus.subscribe(this, &MyLevel::handleInputHold);
		eventBus.subscribe(this, &MyLevel::handleMouseDown);
		eventBus.subscribe(this, &MyLevel::handleMouseUp);
		eventBus.subscribe(this, &MyLevel::handleMouseDrag);
		eventBus.subscribe(this, &MyLevel::handleMouseScroll);

		engine::Shader shader = shaderManager.addShader("basic", (char*)"shaders/vertexshader.glsl", (char*)"shaders/fragmentshader.glsl");

		/*engine::Entity* e = new engine::Entity("test");

		engine::BiomeType biomes[] = {
			engine::BiomeType::GRASS,
			engine::BiomeType::WATER,
			engine::BiomeType::GRASS,
			engine::BiomeType::WATER,
			engine::BiomeType::GRASS,
			engine::BiomeType::WATER,
			engine::BiomeType::GRASS
		};
		auto tile = engine::WorldTile(biomes);
		tile.generate();

		auto rc = new engine::RenderComponent(tile);
		rc->shaders.push_back(shader);
		e->addComponent(rc);
		e->addComponent(new engine::PositionComponent(glm::vec2(5, 0)));
		entityManager.addEntity(e);*/
		terrainGenerator = new engine::TerrainGenerator(entityManager, shaderManager, new engine::NoiseGenerator());

		terrainGenerator->generate(50, 50);

	}
	virtual void initialise() override {
		SystemGameState::initialise();
	}
	virtual void load() override { std::cout << "load" << std::endl; }
	virtual void render() override {
		SystemGameState::render();
	}
	virtual void update(double dt) override {
		SystemGameState::update(dt);
	}
	virtual void unload() override { std::cout << "unload" << std::endl; }

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
		std::stringstream ss;
		ss << "Mouse button down: " << k->button << " at (" << k->data.x << ", " << k->data.y << ")";
		engine::Logger::debug(ss);
	}

	void handleMouseUp(engine::MouseButtonUpEvent* k) {
		std::stringstream ss;
		ss << "Mouse button up: " << k->button << " at (" << k->data.x << ", " << k->data.y << ")";
		engine::Logger::debug(ss);
	}

	void handleMouseDrag(engine::MouseDragEvent* k) {
		std::stringstream ss; 
		ss << "Mouse drag (" << k->button << ") [" << k->dx << ", " << k->dy << "]";
		engine::Logger::debug(ss);
	}

	void handleMouseScroll(engine::MouseScrollEvent* k) {
		std::stringstream ss;
		ss << "Mouse scroll [" << k->dx << ", " << k->dy << "]";
		engine::Logger::debug(ss);
	}


};