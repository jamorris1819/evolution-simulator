#pragma once
#include "entity.h"
#include "eventbus.h"

namespace engine {
	enum class SystemType {
		RENDER = 0x1
	};

	enum class SystemAction {
		UPDATE = 0x1,
		RENDER = 0x2
	};

	class System {
	public:
		System(EventBus& eb) : eventBus(eb), mask(ComponentType::NONE) {}
		virtual SystemType getType() const = 0;
		virtual SystemAction getAction() const = 0;
		virtual void action(Entity* entity) = 0;
		ComponentType mask;
	protected:
		EventBus& eventBus;
	};
}