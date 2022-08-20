#include "Renderer.h"

#include "../Toolbox/Maths.h"

void Renderer::prepare()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapInterval(1);
}

void Renderer::render(Entity& entity, StaticShader& shader)
{
	TexturedModel texturedModel = entity.getModel();
	RawModel rawModel = texturedModel.getModel();

	glBindVertexArray(rawModel.getVaoID());
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glm::mat4 transformationMatrix = Maths::createTransformation(entity.getPosition(), entity.getRotationX(), entity.getRotationY(), entity.getRotationZ(), entity.getScale());

	shader.loadTransformationMatrix(transformationMatrix);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturedModel.getTexture().getID());

	glDrawElements(GL_TRIANGLES, rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glBindVertexArray(0);
}

Renderer::Renderer(StaticShader& shader, float aspectRatio)
{
	// glEnable(GL_CULL_FACE);
	// glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	_projectionMatrix = glm::perspective(_FOV, aspectRatio, _NEAR_PLANE, _FAR_PLANE);
	shader.start();
	shader.loadProjectionMatrix(_projectionMatrix);
	shader.stop();
}
