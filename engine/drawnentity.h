#pragma once
#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/transform.hpp"
#include "GL/glew.h"
#include "polygon.h"
#include "body.h"
#include "entity.h"

/// The DrawnEntity allows us to render Entities with their meshes into our scene.
namespace eng {
	class DrawnEntity : public Entity {
	public:
		DrawnEntity(glm::vec3 position, glm::vec3 scale);
		DrawnEntity(glm::vec3 position) : DrawnEntity(position, glm::vec3(1, 1, 1)) {}
		virtual ~DrawnEntity();

		virtual glm::vec3 const& getPosition() const;
		virtual glm::vec3 const& getVelocity() const;
		virtual glm::vec3 const& getScale() const;
		virtual float getRotation() const;

		virtual void setPosition(glm::vec3 position);
		virtual void setVelocity(glm::vec3 velocity);
		virtual void setScale(glm::vec3 scale);
		virtual void setRotation(float rotation);

		eng::VertexArray const& getVertexArray() const { return vertexArray; }
		void setVertexArray(eng::VertexArray const& va) { vertexArray = va; }
		glm::mat4 getMatrix() const;

		virtual void update(double deltaTime) {};
		void render();
		void load();
		void unload();

		bool isEnabled() { return enabled; }
		void setEnabled(bool enabled) { this->enabled = enabled; }

		bool isVisible() const { return visible; }
		void setVisible(bool v) { visible = v; }

	protected:
		glm::vec3 position;
		glm::vec3 velocity;
		glm::vec3 scale;
		bool enabled;
		bool visible;
		float rotation;
		bool loaded = false;
		eng::VertexArray vertexArray;
		eng::VertexArrayObject vao;
	};
}