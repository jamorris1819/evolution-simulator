#pragma once
#include "system.h"
#include "moveevent.h"

namespace engine {
	class RenderSystem : public System {
	public:
		RenderSystem(EventBus& eb) : System(eb) { mask = ComponentType::POSITION | ComponentType::RENDER; }
		virtual SystemType getType() const override { return SystemType::RENDER; }
		virtual SystemAction getAction() const override { return SystemAction::RENDER; }
		virtual void action(Entity* entity) override;
	};
}