#include "Entity.h"

Entity::Entity()
{
	shaderID = -1;
}


void Entity::unload()
{
	shaderID = -1;
}
