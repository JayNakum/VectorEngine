#pragma once

#include <glm/glm.hpp>

class Light
{
public:
	Light(glm::vec3 position, glm::vec3 color);
	inline glm::vec3 getPosition() { return _position; }
	inline glm::vec3 getColor() { return _color; }
private:
	glm::vec3 _position;
	glm::vec3 _color;
};
