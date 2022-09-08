#include "Application.h"

#include "Vector/Log.h"

#include "Vector/RenderEngine/MasterRenderer.h"
#include "Vector/RenderEngine/Loader.h"
#include "Vector/RenderEngine/OBJLoader.h"

#include "Vector/Shaders/StaticShader.h"

#include "Vector/Textures/ModelTexture.h"

#include "Vector/Models/TexturedModel.h"

#include "Vector/Entities/Entity.h"
#include "Vector/Entities/Camera.h"
#include "Vector/Entities/Light.h"

void Application::go()
{
    Loader loader;
    StaticShader shader;

    RawModel model = OBJLoader::loadObjModel("box", loader);
    ModelTexture texture(loader.loadTexture("box", false));

    texture.setShineDamper(10.0f);
    texture.setReflectivity(1.0f);
    TexturedModel texturedModel(model, texture);

    Entity entity(texturedModel, glm::vec3(0.0f, 0.0f, -25.0f), 0.0f, 0.0f, 0.0f, 1.0f);
    Light light(glm::vec3(0, 0, -20), glm::vec3(1, 1, 1));

    ModelTexture terrain(loader.loadTexture("lamp", true));
    Terrain terrain1(0, 0, loader, terrain);
    Terrain terrain2(1, 0, loader, terrain);

    Camera camera;

    MasterRenderer mRenderer(_window->getAspectRatio());

    while (!_window->isCloseRequested())
    {
        entity.changeRotation(0, 1, 0);
        camera.move();
        
        mRenderer.processTerrain(terrain1);
        mRenderer.processTerrain(terrain2);

        mRenderer.processEntity(entity);
        mRenderer.render(light, camera);

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