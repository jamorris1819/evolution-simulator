#pragma once
#include "../render/polygon.h"

class Hex : public PolygonR {
public:
	Hex(glm::vec2 position, GLuint program);
	void generate();
	void render();
private:
	glm::vec3 position;
};