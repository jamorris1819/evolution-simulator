#pragma once
#include "component.h"
#include "glm/vec2.hpp"

namespace engine {
	/// <summary>
	/// Component holding position data
	/// </summary>
	class PositionComponent : public Component {
	public:
		/// <summary>
		/// Creates a component holding position data
		/// </summary>
		PositionComponent() : PositionComponent(glm::vec2(0, 0)) {}

		/// <summary>
		/// Creates a component holding position data
		/// </summary>
		/// <param name="pos">The position to set</param>
		PositionComponent(glm::vec2 pos) : position(pos) {}

		/// <summary>
		/// The type of component
		/// </summary>
		virtual ComponentType getType() const override { return ComponentType::POSITION; }

		glm::vec2 position;
	};
}