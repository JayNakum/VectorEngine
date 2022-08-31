#include "Renderer.h"

#include "../Toolbox/Maths.h"

void Renderer::prepare()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwSwapInterval(1);
}

/*
void Renderer::render(Entity& entity, StaticShader& shader)
{
	TexturedModel texturedModel = entity.getModel();
	RawModel rawModel = texturedModel.getModel();

	glBindVertexArray(rawModel.getVaoID());
	
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	
	glm::mat4 transformationMatrix = Maths::createTransformation(entity.getPosition(), entity.getRotationX(), entity.getRotationY(), entity.getRotationZ(), entity.getScale());
	shader.loadTransformationMatrix(transformationMatrix);
	
	ModelTexture texture = texturedModel.getTexture();
	shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texturedModel.getTexture().getID());

	glDrawElements(GL_TRIANGLES, rawModel.getVertexCount(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindVertexArray(0);
}
*/

void Renderer::render(std::unordered_map<TexturedModel, std::vector<Entity>, tmCompare>& entities)
{
	for (auto& key : entities)
	{
		bindTexturedModel(key.first);
		for (Entity entity : key.second)
			renderEntity(entity);
		unbindTexturedModel();
	}
}

void Renderer::bindTexturedModel(TexturedModel texturedModel)
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

void Renderer::renderEntity(Entity& entity)
{
	_shader.loadTransformationMatrix(Maths::createTransformation(entity.getPosition(), entity.getRotationX(), entity.getRotationY(), entity.getRotationZ(), entity.getScale()));

	glDrawElements(GL_TRIANGLES, entity.getModel().getRawModel().getVertexCount(), GL_UNSIGNED_INT, 0);
}

void Renderer::unbindTexturedModel()
{
	for (unsigned int i = 0; i < 3; i++)
		glDisableVertexAttribArray(i);
	glBindVertexArray(0);
}

Renderer::Renderer(StaticShader& shader)
	: _shader(shader)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.3137f, 0.0f, 0.0f, 1.0f);
}
