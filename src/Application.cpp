#include "Application.h"

#include "Yarn/Log.h"

#include "Yarn/RenderEngine/Renderer.h"
#include "Yarn/RenderEngine/Loader.h"
#include "Yarn/RenderEngine/OBJLoader.h"

#include "Yarn/Shaders/StaticShader.h"

#include "Yarn/Textures/ModelTexture.h"

#include "Yarn/Models/TexturedModel.h"

#include "Yarn/Entities/Entity.h"
#include "Yarn/Entities/Camera.h"
#include "Yarn/Entities/Light.h"

void Application::go()
{
    Loader loader;
    StaticShader shader;
    Renderer renderer(shader, _window->getAspectRatio());

    RawModel model = OBJLoader::loadObjModel("dragon", loader);
    ModelTexture texture(loader.loadTexture("dragon"));

    texture.setShineDamper(10.0f);
    texture.setReflectivity(1.0f);
    TexturedModel texturedModel(model, texture);

    Entity entity(texturedModel, glm::vec3(0.0f, 0.0f, -25.0f), 0.0f, 0.0f, 0.0f, 1.0f);
    Light light(glm::vec3(0, 0, -20), glm::vec3(1, 1, 1));

    Camera camera;

    while (!_window->isCloseRequested())
    {
        entity.changeRotation(0, 1, 0);
        camera.move();
        renderer.prepare();
        shader.start();
        shader.loadLight(light);
        shader.loadViewMatrix(camera);
        renderer.render(entity, shader);
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