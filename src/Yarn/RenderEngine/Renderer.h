#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Shaders/StaticShader.h"
#include "../Models/TexturedModel.h"
#include "../Entities/Entity.h"

class Renderer
{
public:
	void prepare();
	void render(Entity& entity, StaticShader& shader);

	Renderer(StaticShader& shader, float aspectRatio);

private:
	glm::mat4 _projectionMatrix = glm::mat4(1.0f);
	const float _FOV = 70;
	const float _NEAR_PLANE = 0.1f;
	const float _FAR_PLANE = 1000.0f;
};
