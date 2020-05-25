#include "pch.h"
#include "entitymanager.h"

namespace engine {
	void EntityManager::addEntity(Entity* entity) {
		std::unique_ptr<Entity> pointer(entity);

		entities.push_back(std::move(pointer));
	}

	std::vector<std::unique_ptr<Entity>>& EntityManager::getEntities() {
		return entities;
	}
}