#include "Yarn/Window.h"
#include "Yarn/Loader.h"
#include "Yarn/Renderer.h"

int main(void)
{
	Window window("Yarn Engine", 1280, 720);

	Loader loader;
	Renderer renderer;

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

	RawModel model = loader.loadToVAO(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));

	while (!window.isCloseRequested())
	{
		renderer.prepare();

		renderer.render(model);

		window.update();
		glfwPollEvents();
	}

	glfwTerminate();
}