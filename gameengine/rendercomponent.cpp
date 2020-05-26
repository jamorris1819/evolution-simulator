#include "pch.h"
#include "rendercomponent.h"

namespace engine {
	RenderComponent::RenderComponent() {
		vao.initialise();
	}

	RenderComponent::RenderComponent(const VertexArray& data) : RenderComponent() {
		setData(data);
	}

	const VertexArray& RenderComponent::getData() const {
		return vao.getVertexArray();
	}

	void RenderComponent::setData(const VertexArray& data) {
		vao.setVertexArray(data);
		vao.load();
	}
}
