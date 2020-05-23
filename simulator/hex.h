#pragma once

#include "vertexarray.h"

class Hex : public eng::VertexArray {
public:
	Hex(int size);
	void virtual generate() override;
private:
	int size;
};