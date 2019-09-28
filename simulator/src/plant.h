#pragma once
#include "livingentity.h"
#include "plantbody.h"

class Plant : public LivingEntity {
public:
	Plant(GLuint shader, b2World* world, glm::vec3 position);
	void generate();
};