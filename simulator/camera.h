#pragma once
#include "glm/mat4x4.hpp"
#include "GL/glew.h"
#include "entity.h"

class Camera : public eng::Entity {
public:
	Camera(glm::vec2 position, GLuint shaderID);
	glm::mat4 view;
	glm::mat4 projection;
	glm::vec4 viewport;
	bool enabled;
	void initialise(float width, float height, float speed);
	void align();
	void update(double deltaTime);
	bool handleMovement(double deltaTime);
	bool handleZoom(double deltaTime);
	float zoom;
	void updateWindowBounds(int width, int height);
	glm::vec2 position;
protected:
	int ppm;
	float minZoom;
	float maxZoom;
	int width;
	int height;
	float moveSpeed;

	void createProjection();
};
