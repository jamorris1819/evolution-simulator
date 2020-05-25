#pragma once
#include "component.h"
namespace engine {
	class RotationComponent : public Component {
	public:
		RotationComponent() : RotationComponent(0.0) {}
		RotationComponent(double rot) { rotation = rot; }
		virtual ComponentType getType() const override { return ComponentType::ROTATION; }
		double rotation;
	};
}