#pragma once
#include "menuwindow.h"
#include "terrainmanager.h"
#include "entitymanager.h"

class WorldWindow : public MenuWindow {
public:
	TerrainManager* terrain;
	EntityManager* entityManager;
	void initialise() override;
	void renderWindow() override;
};