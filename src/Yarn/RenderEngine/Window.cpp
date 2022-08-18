#include "Window.h"

#include "../Log.h"

void Window::update()
{
    if (_updateViewport)
    {
        glfwGetFramebufferSize(_glfwWindow, &_viewportWidth, &_viewportHeight);
        glViewport(0, 0, _viewportWidth, _viewportHeight);
        _updateViewport = false;
    }       

    glfwSwapBuffers(_glfwWindow);  
}

bool Window::isCloseRequested()
{
    return glfwWindowShouldClose(_glfwWindow);
}

void Window::callbackResize(GLFWwindow* window, int width, int height)
{
    void* ptr = glfwGetWindowUserPointer(window);
    if (Window* wndPtr = static_cast<Window*>(ptr))
        wndPtr->resize(width, height);
}

void Window::resize(int width, int height)
{
    _updateViewport = true;
}

bool Window::isFullscreen(void)
{
    return glfwGetWindowMonitor(_glfwWindow) != nullptr;
}

void Window::setFullScreen(bool fullscreen)
{
    if (isFullscreen() == fullscreen)
        return;

    if (fullscreen)
    {
        // backup window position and window size
        glfwGetWindowPos(_glfwWindow, &_xPos, &_yPos);
        glfwGetWindowSize(_glfwWindow, &_width, &_height);

        // get resolution of monitor
        const GLFWvidmode* mode = glfwGetVideoMode(_monitor);

        // switch to full screen
        glfwSetWindowMonitor(_glfwWindow, _monitor, 0, 0, mode->width, mode->height, 0);
    }
    else
    {
        // restore last window size and position
        glfwSetWindowMonitor(_glfwWindow, nullptr, _xPos, _yPos, _width, _height, 0);
    }

    _updateViewport = true;
}

Window::Window(const char* title, int width, int height)
    : _width(width), _height(height)
{
    _glfwWindow = glfwCreateWindow(_width, _height, title, nullptr, nullptr);
    if (_glfwWindow == nullptr)
    {
        glfwTerminate();
        ERROR("error initializing window");
    }

    glfwMakeContextCurrent(_glfwWindow);

    glfwSetWindowUserPointer(_glfwWindow, this);
    glfwSetWindowSizeCallback(_glfwWindow, Window::callbackResize);

    _monitor = glfwGetPrimaryMonitor();
    glfwGetWindowSize(_glfwWindow, &_width, &_height);
    glfwGetWindowPos(_glfwWindow, &_xPos, &_yPos);

    _aspectRatio = (float)_width / (float)_height;
    _updateViewport = true;
}

Window::~Window()
{
    glfwDestroyWindow(_glfwWindow);
}
