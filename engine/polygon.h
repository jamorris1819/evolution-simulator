#pragma once
#include "GL\glew.h"
#include <vector>
#include "vertex.h"
#include "triangle.h"
#include "vertexarrayobject.h"
#include "vertexarray.h"

using namespace std;

class PolygonData : public VertexArray {
public:
	PolygonData(GLuint shaderID);
	~PolygonData();
	void load();
	void unload();
	void render(glm::mat4 matrix);
	GLuint shaderID;
	VertexArrayObject* vao;
	void enableOverrideColour(glm::vec3 overrideColour);
	void setVisible(bool visible) { this->visible = visible; }
	bool isVisible() const { return visible; }
protected:
	glm::vec3 overrideColour;
	void setColour();
	bool visible;
private:
	bool useOverrideColour;
};
