#include "EntityRenderer.h"

#include "../Toolbox/Maths.h"

void EntityRenderer::render(std::map<TexturedModel, std::list<Entity>, tmCompare>& entities)
{
	for (auto& key : entities)
	{
		bindTexturedModel(key.first);
		for (Entity entity : key.second)
			renderEntity(entity);
		unbindTexturedModel();
	}
}

void EntityRenderer::bindTexturedModel(TexturedModel texturedModel)
{
	RawModel model = texturedModel.getRawModel();

	glBindVertexArray(model.getVaoID());

	for (unsigned int i = 0; i < 3; i++)
		glEnableVertexAttribArray(i);

	ModelTexture texture = texturedModel.getTexture();
	_shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturedModel.getTexture().getID());
}

void EntityRenderer::renderEntity(Entity& entity)
{
	_shader.loadTransformationMatrix(Maths::createTransformation(entity.getPosition(), entity.getRotationX(), entity.getRotationY(), entity.getRotationZ(), entity.getScale()));

	glDrawElements(GL_TRIANGLES, entity.getModel().getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
}

void EntityRenderer::unbindTexturedModel()
{
	for (unsigned int i = 0; i < 3; i++)
		glDisableVertexAttribArray(i);
	glBindVertexArray(0);
}

EntityRenderer::EntityRenderer(StaticShader& shader, glm::mat4 projectionMatrix)
	: _shader(shader)
{
	_shader.start();
	_shader.loadProjectionMatrix(projectionMatrix);
	_shader.stop();
}
