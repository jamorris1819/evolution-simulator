#pragma once
#include "component.h"
#include <vector>
#include "vertexarrayobject.h"
#include "shader.h"

namespace engine {
	class RenderComponent : public Component {
	public:
		RenderComponent();
		RenderComponent(const VertexArray& data);

		virtual ComponentType getType() const override { return ComponentType::RENDER; }

		std::vector<Shader> shaders;
		const VertexArray& getData() const;
		void setData(const VertexArray& data);

	private:
		VertexArrayObject vao;
	};
}