#pragma once
#include "component.h"
#include <vector>
#include "vertexarrayobject.h"
#include "shader.h"

namespace engine {
	/// <summary>
	/// Component holding render data
	/// </summary>
	class RenderComponent : public Component {
	public:
		/// <summary>
		/// Creates a component which can hold and render vertex data
		/// </summary>
		RenderComponent();

		/// <summary>
		/// Creates a component which holds and renders vertex data
		/// </summary>
		/// <param name="data">The vertex data object to set</param>
		RenderComponent(const VertexArray& data);

		/// <summary>
		/// Get the type of component
		/// </summary>
		/// <returns></returns>
		virtual ComponentType getType() const override { return ComponentType::RENDER; }

		/// <summary>
		/// Returns const ref to the vertex data currently held
		/// </summary>
		const VertexArray& getData() const;

		/// <summary>
		/// Set the vertex data to be held
		/// </summary>
		/// <param name="data">Vertex data to be set</param>
		void setData(const VertexArray& data);

		std::vector<Shader> shaders;
		VertexArrayObject vao;
	};
}