#pragma once
#include "plantbody.h"

class BushBody : public PlantBody {
public:
	BushBody(GLuint shader, b2World* world);
	void generateBodyPoints();
	void setVisibleFruit(int i);
	vector<eng::VertexRenderer*> fruit;
};