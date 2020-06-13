#pragma once
#include "component.h"
#include "glm/vec2.hpp"

namespace engine {
	/// <summary>
	/// Component holding velocity data
	/// </summary>
	class VelocityComponent : public Component {
	public:
		/// <summary>
		/// Creates a component for velocity data
		/// </summary>
		VelocityComponent() : VelocityComponent(glm::vec2(0, 0)) {}

		/// <summary>
		/// Creates a component with the given velocity data
		/// </summary>
		/// <param name="vel">Velocity data to set</param>
		VelocityComponent(glm::vec2 vel) : velocity(vel) {}

		/// <summary>
		/// Get the component type
		/// </summary>
		virtual ComponentType getType() const override { return ComponentType::VELOCITY; }

		glm::vec2 velocity;
	};
}