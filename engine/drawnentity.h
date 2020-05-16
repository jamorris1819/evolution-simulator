#pragma once

#include "glm/vec3.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/transform.hpp"
#include "GL/glew.h"
#include "polygon.h"
#include "body.h"
#include "entity.h"

using namespace std;

/// The DrawnEntity allows us to render Entities with their meshes into our scene.

class DrawnEntity : public Entity {
public:
	DrawnEntity(glm::vec3 position);
	DrawnEntity(glm::vec3 position, glm::vec3 scale);
	~DrawnEntity();
	bool enabled;
	glm::vec3 const& getPosition() const;
	glm::vec3 const& getVelocity() const;
	glm::vec3 const& getScale() const;
	float getRotation() const;
	PolygonData const* getPolygon() const;
	glm::mat4 getMatrix() const;
	void setPosition(glm::vec3 position);
	void setVelocity(glm::vec3 velocity);
	void setScale(glm::vec3 scale);
	void setRotation(float rotation);
	void setPolygon(PolygonData* polygon);
	void setBody(Body* body);
	virtual void update(double deltaTime);
	void render();
	void load() override;
	void unload();
	Body* body;

protected:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 scale;
	float rotation;
	PolygonData* polygon;
};
