#include "Application.h"

#include "Yarn/Log.h"

#include "Yarn/RenderEngine/Renderer.h"
#include "Yarn/RenderEngine/Loader.h"

#include "Yarn/Shaders/StaticShader.h"

#include "Yarn/Textures/ModelTexture.h"

#include "Yarn/Models/TexturedModel.h"

void Application::go()
{
    Loader loader;
    Renderer renderer;
    StaticShader shader;

    float vertices[] = {
        -0.5f,  0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f
    };

    unsigned int indices[] = {
        0, 1, 3,
        3, 1, 2
    };

    float textureCoords[] = {
        0, 0,
        0, 1,
        1, 1,
        1, 0
    };

    RawModel model = loader.loadToVAO(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]), textureCoords, sizeof(textureCoords) / sizeof(textureCoords[0]));
    ModelTexture texture(loader.loadTexture("image"));
    TexturedModel texturedModel(model, texture);

    while (!_window->isCloseRequested())
    {
        renderer.prepare();
        shader.start();
        renderer.render(texturedModel);
        shader.stop();

        _window->update();
        glfwPollEvents();
    }
}

Application::Application(const char* title)
    : _title(title)
{
    if (!glfwInit())
    {
        ERROR("GLFW INITIALIZATION FAILED");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GL_TRUE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    _window = new Window(_title, 1280, 720);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        ERROR("GLAD INITIALIZATION FAILED");
    }
}

Application::~Application()
{
    delete _window;
    glfwTerminate();
}

int main(void)
{
    Application engine;
    engine.go();
}