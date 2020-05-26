#pragma once
#include <vector>
#include "component.h"
#include <string>
#include <memory>

namespace engine {
	class Entity {
	public:
		Entity(std::string name);
		Entity(const Entity& entity);
		unsigned int getId() const { return id; }
		const std::vector<std::unique_ptr<Component>>& getComponents() const;
		void addComponent(Component*);
		template<typename CompType>
		CompType* getComponent();
		ComponentType getMask() { return mask; }
		const std::string& getName() const { return name; }
	private:
		std::string name;
		unsigned int id;
		std::vector<std::unique_ptr<Component>> components;
		bool hasComponent(ComponentType) const;
		ComponentType mask;
	};

	/// <summary>
	/// Gets a pointer to the specified component.
	/// </summary>
	/// <typeparam name="CompType">The type of component to return</typeparam>
	template<typename CompType>
	CompType* Entity::getComponent() {
		for (auto& component : components) {
			if (CompType* ptr = dynamic_cast<CompType*>(component.get())) {
				return ptr;
			}
		}

		return nullptr;
	}
}