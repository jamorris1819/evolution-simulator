#include "pch.h"
#include "systemmanager.h"

namespace engine {
	/// <summary>
	/// Adds a new system to the manager.
	/// </summary>
	void SystemManager::addSystem(System* system) {
		std::unique_ptr<System> pointer(system);

		systems.push_back(std::move(pointer));
	}

	/// <summary>
	/// Update all systems that identify as having an UPDATE action.
	/// </summary>
	void SystemManager::update(std::vector<std::unique_ptr<Entity>>& entities) {
		for (auto& system : systems) {
			if (system.get()->getAction() == SystemAction::UPDATE) {
				for (auto& entity : entities) {
					system.get()->action(entity.get());
				}
			}
		}
	}

	/// <summary>
	/// Updates all systems that identify as having a RENDER action.
	/// </summary>
	void SystemManager::render(std::vector<std::unique_ptr<Entity>>& entities) {
		for (auto& system : systems) {
			if (system.get()->getAction() == SystemAction::RENDER) {
				for (auto& entity : entities) {
					system.get()->action(entity.get());
				}
			}
		}
	}
}