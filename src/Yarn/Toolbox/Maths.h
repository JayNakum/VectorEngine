#pragma once

#include <glm/glm.hpp>
#include <glm\gtx\transform.hpp>

class Maths
{
public:
	static glm::mat4 createTransformation(glm::vec3 translation, float rx, float ry, float rz, float scale);
};

