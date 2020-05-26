#pragma once
#include "entity.h"

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
		virtual SystemType getType() const = 0;
		virtual SystemAction getAction() const = 0;
		virtual void action(Entity* entity) = 0;
		ComponentType mask;
	};
}