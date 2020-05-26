#include "pch.h"
#include "entity.h"
#include "idmanager.h"

namespace engine {
	/// <summary>
	/// Constructs an empty entity.
	/// </summary>
	Entity::Entity(std::string name) {
		id = IdManager::getNewId();
		this->name = name;
		mask = ComponentType::NONE;
	}

	Entity::Entity(const Entity& entity) {
		id = entity.id;
		name = entity.name;
		mask = entity.mask;

		for (int i = 0; i < entity.components.size(); i++) {
			
		}
	}

	/// <summary>
	/// Attaches a component to the entity.
	/// </summary>
	void Entity::addComponent(Component* component) {
		if (hasComponent(component->getType())) return;

		std::unique_ptr<Component> pointer(component);

		components.push_back(std::move(pointer));
		mask |= component->getType();
	}

	/// <summary>
	/// Determine whether the specified component type is attached to the entity.
	/// </summary>
	bool Entity::hasComponent(ComponentType type) const {
		for (const auto& component : components) {
			if (component->getType() == type) return true;
		}

		return false;
	}

	/// <summary>
	/// Gets the components attached to the entity.
	/// </summary>
	const std::vector<std::unique_ptr<Component>>& Entity::getComponents() const {
		return components;
	}
}