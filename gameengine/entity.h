#pragma once
#include <vector>
#include "component.h"
#include <string>
#include <memory>

namespace engine {
	/// <summary>
	/// A base class for game objects which can hold components
	/// </summary>
	class Entity {
	public:
		Entity(std::string name);
		Entity(const Entity& entity);

		/// <summary>
		/// Gets the unique id of this entity
		/// </summary>
		unsigned int getId() const { return id; }

		/// <summary>
		/// Get the collection of components attached
		/// </summary>
		const std::vector<std::unique_ptr<Component>>& getComponents() const;

		/// <summary>
		/// Adds the given component to this entity
		/// </summary>
		void addComponent(Component* component);

		template<typename CompType>
		CompType* getComponent();

		/// <summary>
		/// Gets the bitmask representing which components are atatched
		/// </summary>
		/// <returns></returns>
		ComponentType getMask() { return mask; }

		/// <summary>
		/// Gets the name of the entity
		/// </summary>
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