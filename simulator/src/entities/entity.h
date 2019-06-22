#pragma once
#include "GL/glew.h"

// An entity represents any object that is present in a scene, regardless of if it's visible.
class Entity
{
public:
	Entity();
	void unload();
protected:
	GLuint shaderID;
};
