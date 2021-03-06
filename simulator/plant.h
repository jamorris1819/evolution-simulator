#pragma once
#include "livingentity.h"
#include "plantbody.h"

class Plant : public LivingEntity {
public:
	Plant(GLuint shader, glm::vec3 position);
	virtual void generate();
};