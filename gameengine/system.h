#pragma once
#include "entity.h"

namespace engine {
	enum class SystemType {

	};

	class System {
	public:
		virtual SystemType getType() const = 0;
		virtual void update(Entity& entity) = 0;
	};
}