#pragma once
#include "GL\glew.h"
#include <vector>
#include "vertex.h"
#include "triangle.h"
#include "vertexarrayobject.h"
#include "vertexarray.h"

using namespace std;

class PolygonR : public VertexArray
{
public:
	PolygonR(GLuint shaderID);
	~PolygonR();
	void load();
	void unload();
	void render(glm::mat4 matrix);
	GLuint shaderID;
	VertexArrayObject* vao;
	void enableOverrideColour(glm::vec3 overrideColour);
	bool visible;
protected:
	glm::vec3 overrideColour;
	void setColour();
private:
	bool useOverrideColour;
};
