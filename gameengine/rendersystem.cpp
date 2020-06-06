#include "pch.h"
#include "rendersystem.h"
#include "rendercomponent.h"
#include "positioncomponent.h"
#include <glm/gtc/matrix_transform.hpp> 

namespace engine {
	void RenderSystem::action(Entity* entity, double dt) {
		if ((entity->getMask() & mask) != mask) return;

		RenderComponent* rc = entity->getComponent<RenderComponent>();
		PositionComponent* pc = entity->getComponent<PositionComponent>();

		glm::mat4 matrix = glm::translate(glm::mat4(1.0f), glm::vec3(pc->position, 0));

		// Render the shape with every shader.
		for (Shader& shader : rc->shaders) {
			shader.bind();
			shader.setUniformMat4("uModel", matrix);
			rc->vao.render();
		}
	}
}