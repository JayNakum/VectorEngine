#include "Entity.h"

Entity::Entity(TexturedModel& model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale)
	: _model(model), _position(position), _rotX(rotX), _rotY(rotY), _rotZ(rotZ), _scale(scale) {}

void Entity::changePosition(float dx, float dy, float dz)
{
	_position.x += dx;
	_position.y += dy;
	_position.z += dz;
}

void Entity::changeRotation(float dx, float dy, float dz)
{
	_rotX += dx;
	_rotY += dy;
	_rotZ += dz;
}