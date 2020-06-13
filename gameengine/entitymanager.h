#pragma once
#include <memory>
#include <vector>
#include "entity.h"

namespace engine {
	/// <summary>
	/// Manages the lifetime of entities in the system
	/// </summary>
	class EntityManager {
	public:
		/// <summary>
		/// Adds the entity into the manager for the remainder of its lifetime
		/// </summary>
		void addEntity(Entity* entity);

		/// <summary>
		/// Retrieve a reference to the list of entities
		/// </summary>
		std::vector<std::unique_ptr<Entity>>& getEntities();
	private:
		std::vector<std::unique_ptr<Entity>> entities;
	};
}