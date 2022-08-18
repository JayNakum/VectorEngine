#include "Application.h"

#include "Yarn/Log.h"

#include "Yarn/RenderEngine/Renderer.h"
#include "Yarn/RenderEngine/Loader.h"

#include "Yarn/Shaders/StaticShader.h"

#include "Yarn/Textures/ModelTexture.h"

#include "Yarn/Models/TexturedModel.h"
#include "Yarn/Entities/Entity.h"
#include "Yarn/Entities/Camera.h"

void Application::go()
{
    Loader loader;
    StaticShader shader;
    Renderer renderer(shader, _window->getAspectRatio());

	float vertices[] = {
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,

		-0.5f, 0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,

		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,

		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,

		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f,

		-0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f
	};

	unsigned int indices[] = {
		0, 1, 3,
		3, 1, 2,
		4, 5, 7,
		7, 5, 6,
		8, 9, 11,
		11, 9, 10,
		12, 13, 15,
		15, 13, 14,
		16, 17, 19,
		19, 17, 18,
		20, 21, 23,
		23, 21, 22
	};

	float textureCoords[] = {
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0,
		0, 0,
		0, 1,
		1, 1,
		1, 0
	};

    RawModel model = loader.loadToVAO(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]), textureCoords, sizeof(textureCoords) / sizeof(textureCoords[0]));
    ModelTexture texture(loader.loadTexture("image"));
    TexturedModel texturedModel(model, texture);

    Entity entity(texturedModel, glm::vec3(0.0f, 0.0f, -5.0f), 0.0f, 0.0f, 0.0f, 1.0f);

    Camera camera;

    while (!_window->isCloseRequested())
    {
		entity.changeRotation(1, 1, 0);
        camera.move();
        renderer.prepare();
        shader.start();
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