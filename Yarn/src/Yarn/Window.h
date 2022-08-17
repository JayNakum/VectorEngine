#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	Window(const char* title, int width, int height);
	~Window();

	void update();

	bool isCloseRequested();

	bool isFullscreen();
	void setFullScreen(bool fullscreen);

private:
	static void callbackResize(GLFWwindow* window, int width, int height);
	void resize(int width, int height);

	int _width, _height;
	int _xPos = 0, _yPos = 0;
	int _viewportWidth = 0, _viewportHeight = 0;
	bool _updateViewport = true;
	
	GLFWwindow* _glfwWindow;
	GLFWmonitor* _monitor;
};
