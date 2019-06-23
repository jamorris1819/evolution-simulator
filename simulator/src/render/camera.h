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
	void initialise(float width, float height, float speed);
	void align();
	void update(double deltaTime);
protected:
	float moveSpeed;
	glm::vec2 position;
	glm::mat4 projection;
};
