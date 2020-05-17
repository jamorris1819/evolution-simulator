#pragma once
#include "polygon.h"

class Hex : public eng::VertexRenderer {
public:
	Hex(int size, glm::vec2 position, GLuint program);
	void generate();
	void render();
	void update(double deltaTime);
	bool getFade();
	void setFade(bool fade);
	int getFadeOffset();
	void setFadeOffset(int fadeOffset);
	int originalX;
	int originalY;
private:
	glm::vec3 position;
	glm::vec3 colour;
	int size;
	double time;
	bool fade;
	int fadeOffset;
};