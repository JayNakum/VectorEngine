#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Yarn/RenderEngine/Window.h"

class Application
{
public:
	Application(const char* title = "Yarn Engine");
	~Application();

	void go();
private:
	const char* _title;
	Window* _window;
};

