#pragma once
#include "componenttype.h"
#include <string>
#include <memory>

namespace engine {
	class Component {
	public:
		virtual ComponentType getType() const = 0;
	};
}