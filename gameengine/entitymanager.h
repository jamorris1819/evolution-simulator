#pragma once
#include <memory>
#include <vector>
#include "entity.h"

namespace engine {
	class EntityManager {
	public:
		void addEntity(Entity* entity);
		std::vector<std::unique_ptr<Entity>>& getEntities();
	private:
		std::vector<std::unique_ptr<Entity>> entities;
	};
}