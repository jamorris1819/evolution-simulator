#pragma once
#include "component.h"
namespace engine {
	/// <summary>
	/// Component holding rotation data
	/// </summary>
	class RotationComponent : public Component {
	public:
		/// <summary>
		/// Creates a component that can hold rotation data
		/// </summary>
		RotationComponent() : RotationComponent(0.0) {}

		/// <summary>
		/// Creates a component holding rotation data
		/// </summary>
		/// <param name="rot">Rotation to be set</param>
		RotationComponent(double rot) : rotation(rot) {}

		/// <summary>
		/// Get the type of component
		/// </summary>
		virtual ComponentType getType() const override { return ComponentType::ROTATION; }

		double rotation;
	};
}