#include "pch.h"
#include "Entity.h"

namespace eng {
	Entity::Entity() {
		shaderID = -1;
	}

	void Entity::unload() {
		shaderID = -1;
	}
}