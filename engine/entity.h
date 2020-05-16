#pragma once
#include "GL\glew.h"

// An entity represents any object that is present in a scene, regardless of if it's visible.
class Entity {
public:
	Entity();
	virtual void load() = 0;
	void unload();
protected:
	GLuint shaderID;
};
