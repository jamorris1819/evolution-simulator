#include "pch.h"
#include "DrawnEntity.h"
#include "polygon.h"
#include <thread>

namespace eng {
	DrawnEntity::DrawnEntity(glm::vec3 position, glm::vec3 scale) : Entity() {
		enabled = true;
		setPosition(position);
		setVelocity(glm::vec3(0, 0, 0));
		setScale(scale);
		setRotation(0);
	}

	DrawnEntity::~DrawnEntity() {
		delete vao;
	}

	glm::vec3 const& DrawnEntity::getPosition() const {
		return position;
	}

	glm::vec3 const& DrawnEntity::getVelocity() const {
		return velocity;
	}

	glm::vec3 const& DrawnEntity::getScale() const {
		return scale;
	}

	float DrawnEntity::getRotation() const {
		return -body->getRotation();
	}

	glm::mat4 DrawnEntity::getMatrix() const {
		// Create translation matrix.
		glm::mat4 matrix = glm::translate(glm::mat4(1.0f), position);
		// Apply rotation matrix.
		matrix = glm::rotate(matrix, body->getRotation(), glm::vec3(0.0f, 0.0f, 1.0f));

		return matrix;
	}

	void DrawnEntity::setPosition(glm::vec3 position) {
		this->position = position;
	}

	void DrawnEntity::setVelocity(glm::vec3 velocity) {
		this->velocity = velocity;
	}

	void DrawnEntity::setScale(glm::vec3 scale) {
		this->scale = scale;
	}

	void DrawnEntity::setRotation(float rotation) {
		this->rotation = rotation;
	}

	void DrawnEntity::setBody(Body* body) {
		this->body = body;
	}

	void DrawnEntity::render() {
		if (enabled)
			body->render(getMatrix());
	}

	void DrawnEntity::update(double deltaTime) {
		if (body != nullptr)
			setPosition(glm::vec3(body->getPosition(), 0.0f));
	}

	void DrawnEntity::unload() {
		//polygon->unload();
	}
}