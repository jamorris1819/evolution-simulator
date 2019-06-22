#pragma once
#include "glm/mat4x4.hpp"
#include "GL/glew.h"
#include "../entities/entity.h"

class Camera : public Entity
{
public:
	Camera(glm::vec2 position, GLuint shaderID);
	glm::mat4 view;
	bool enabled;
	void initialise();
	void align();
	void update(double deltaTime);
protected:
	glm::vec2 position;
};
