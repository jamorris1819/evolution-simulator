#pragma once
#include "entity.h"
#include <glm/mat4x4.hpp>

class IDrawable {
public:
	virtual ~IDrawable() {}
	virtual void load() = 0;
	virtual void unload() = 0;
	virtual void render(glm::mat4 matrix) = 0;
private:
	GLuint shaderId;
};