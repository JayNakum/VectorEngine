#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Models/TexturedModel.h"

class Renderer
{
public:
	void prepare();
	void render(TexturedModel& texturedModel);
};
