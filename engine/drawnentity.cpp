#include "pch.h"
#include "DrawnEntity.h"
#include <thread>

namespace eng {
	DrawnEntity::DrawnEntity(GLuint shaderId, glm::vec3 position, glm::vec3 scale) : Entity() {
		enabled = true;
		visible = true;
		setPosition(position);
		setVelocity(glm::vec3(0, 0, 0));
		setScale(scale);
		setRotation(0);

		vao.setShader(shaderId);
		vao.initialise();
	}

	DrawnEntity::~DrawnEntity() {
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
		return rotation; // -body->getRotation();
	}

	void DrawnEntity::setVertexArray(eng::VertexArray const& va) {
		vertexArray = va;
		vao.setVertexArray(vertexArray);
		vao.load();
	}

	glm::mat4 DrawnEntity::getMatrix() const {
		// Create translation matrix.
		glm::mat4 matrix = glm::translate(glm::mat4(1.0f), position);
		// Apply rotation matrix.
		matrix = glm::rotate(matrix, -rotation, glm::vec3(0.0f, 0.0f, 1.0f));

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

	void DrawnEntity::render() {
		if (enabled && visible)
			vao.render(getMatrix());
	}

	void DrawnEntity::load() {
		if (vertexArray.getVertexCount() == 0) return;

		vao.setVertexArray(vertexArray);
		vao.load();
	}

	void DrawnEntity::unload() {
		vao.unload();
	}
}