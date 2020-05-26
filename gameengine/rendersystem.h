#pragma once
#include "system.h"

namespace engine {
	class RenderSystem : public System {
	public:
		RenderSystem() { mask = ComponentType::POSITION | ComponentType::RENDER; }
		virtual SystemType getType() const override { return SystemType::RENDER; }
		virtual SystemAction getAction() const override { return SystemAction::RENDER; }
		virtual void action(Entity* entity) override;
	};
}