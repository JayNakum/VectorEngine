#include "TerrainRenderer.h"

#include "../Toolbox/Maths.h"

TerrainRenderer::TerrainRenderer(TerrainShader& shader, glm::mat4 projectionMatrix)
	: _shader(shader)
{
	_shader.start();
	_shader.loadProjectionMatrix(projectionMatrix);
	_shader.stop();
}

void TerrainRenderer::render(std::list<Terrain> terrains)
{
	for (auto& terrain : terrains)
	{
		bindTerrainModel(terrain);
		renderTerrain(terrain);
		unbindTerrainModel();
	}
}

void TerrainRenderer::bindTerrainModel(Terrain& terrain)
{
	RawModel model = terrain.getModel();

	glBindVertexArray(model.getVaoID());

	for (unsigned int i = 0; i < 3; i++)
		glEnableVertexAttribArray(i);

	ModelTexture texture = terrain.getTexture();
	_shader.loadShineVariables(texture.getShineDamper(), texture.getReflectivity());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.getID());
}

void TerrainRenderer::renderTerrain(Terrain& terrain)
{
	_shader.loadTransformationMatrix(Maths::createTransformation(glm::vec3(terrain.getX(), 0, terrain.getZ()), 0, 0, 0, 1));

	glDrawElements(GL_TRIANGLES, terrain.getModel().getVertexCount(), GL_UNSIGNED_INT, 0);
}

void TerrainRenderer::unbindTerrainModel()
{
	for (unsigned int i = 0; i < 3; i++)
		glDisableVertexAttribArray(i);
	glBindVertexArray(0);
}