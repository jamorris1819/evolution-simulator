#pragma once
#include "../render/polygon.h"

class Hex : public PolygonR {
public:
	Hex(int size, glm::vec2 position, GLuint program);
	void generate();
	void render();
	void update(double deltaTime);
	bool getFade();
	void setFade(bool fade);
	int getFadeOffset();
	void setFadeOffset(int fadeOffset);
private:
	glm::vec3 position;
	glm::vec3 colour;
	int size;
	double time;
	bool fade;
	int fadeOffset;
};