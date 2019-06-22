#include "DrawnEntity.h"
#include "../render/polygon.h"
#include <thread>

DrawnEntity::DrawnEntity(glm::vec3 position) : Entity()
{
	enabled = true;
	setPosition(position);
	setVelocity(glm::vec3(0, 0, 0));
	setScale(glm::vec3(1, 1, 1));
	setRotation(glm::quat());
}

DrawnEntity::DrawnEntity(glm::vec3 position, glm::vec3 scale) : Entity()
{
	enabled = true;
	setPosition(position);
	setVelocity(glm::vec3(0, 0, 0));
	setScale(scale);
	setRotation(glm::quat());
}

glm::vec3& DrawnEntity::getPosition()
{
	return position;
}

glm::vec3& DrawnEntity::getVelocity()
{
	return velocity;
}

glm::vec3& DrawnEntity::getScale()
{
	return scale;
}

glm::quat& DrawnEntity::getRotation()
{
	return rotation;
}

PolygonR* DrawnEntity::getPolygon()
{
	return polygon;
}

glm::mat4 DrawnEntity::getMatrix() const
{
	glm::mat4 translate = glm::translate(glm::mat4(1.0f), position);
	glm::mat4 rotation = glm::rotate(translate, (float)glm::radians(0.0), glm::vec3(0.0f, 1.0f, 0.0f));

	glm::mat4 matrix = translate * rotation;
	return translate;
}

void DrawnEntity::setPosition(glm::vec3 position)
{
	this->position = position;
}

void DrawnEntity::setVelocity(glm::vec3 velocity)
{
	this->velocity = velocity;
}

void DrawnEntity::setScale(glm::vec3 scale)
{
	this->scale = scale;
}

void DrawnEntity::setRotation(glm::quat rotation)
{
	this->rotation = rotation;
}

void DrawnEntity::setPolygon(PolygonR* polygon)
{
	this->polygon = polygon;
}

void DrawnEntity::render()
{
	if (enabled)
		polygon->render(getMatrix());
}

void DrawnEntity::update(float deltaTime)
{
	setPosition(getPosition() + (getVelocity() * deltaTime));
}