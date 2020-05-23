#pragma once
#include "vertexarray.h"
#include "glm\vec2.hpp"
#include <vector>


class Body {
public:
	eng::VertexArray const& getPrimaryBody() const { return primaryBody; }
	std::vector<eng::VertexArray> const& getSecondaryBodies() const { return secondaryBodies; }
	std::vector<eng::VertexArray> getBodies() const { 
		std::vector<eng::VertexArray> bodies = secondaryBodies;
		bodies.insert(bodies.begin(), primaryBody);
		return bodies;
	}
	virtual void generate() = 0;
	
	eng::VertexArray getVertexArray() {
		eng::VertexArray newVA;
		newVA.fromMany(getBodies());
		return newVA;
	}

protected:
	eng::VertexArray primaryBody;
	std::vector<eng::VertexArray> secondaryBodies;
};
