#pragma once
#include "GL\glew.h"
#include <vector>
#include "vertex.h"
#include "triangle.h"
#include "vertexarrayobject.h"
#include "vertexarray.h"

using namespace std;

namespace eng {
	class VertexRenderer : public VertexArray {
	public:
		VertexRenderer(GLuint shaderID);
		~VertexRenderer();
		void load();
		void unload();
		void render(glm::mat4 matrix);
		GLuint shaderID;
		VertexArrayObject* vao;
		void enableOverrideColour(glm::vec3 overrideColour);
		void setVisible(bool visible) { this->visible = visible; }
		bool isVisible() const { return visible; }
		VertexArray const& getRenderData() const { return renderData; }
		void setRenderData(VertexArray const& data) { renderData = data; }
	protected:
		glm::vec3 overrideColour;
		void setColour();
		bool visible;
	private:
		bool useOverrideColour;
		VertexArray renderData;
	};
}