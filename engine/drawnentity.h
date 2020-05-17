#pragma once
#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/transform.hpp"
#include "GL/glew.h"
#include "polygon.h"
#include "body.h"
#include "entity.h"

/// The DrawnEntity allows us to render Entities with their meshes into our scene.

class DrawnEntity : public Entity {
public:
	DrawnEntity(glm::vec3 position);
	DrawnEntity(glm::vec3 position, glm::vec3 scale);
	virtual ~DrawnEntity();

	virtual glm::vec3 const& getPosition() const;
	virtual glm::vec3 const& getVelocity() const;
	virtual glm::vec3 const& getScale() const;
	virtual float getRotation() const;

	virtual void setPosition(glm::vec3 position);
	virtual void setVelocity(glm::vec3 velocity);
	virtual void setScale(glm::vec3 scale);
	virtual void setRotation(float rotation);

	eng::VertexRenderer const* getPolygon() const;
	void setPolygon(eng::VertexRenderer* polygon);
	glm::mat4 getMatrix() const;

	void setBody(Body* body);
	virtual void update(double deltaTime);
	void render();
	void unload();
	Body* body;
	bool isEnabled() { return enabled; }
	void setEnabled(bool enabled) { this->enabled = enabled; }

protected:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 scale;
	bool enabled;
	float rotation;
	eng::VertexRenderer* polygon;
};
