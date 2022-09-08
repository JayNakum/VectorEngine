#pragma once

#include <list>
#include <glm/glm.hpp>

#include "../Shaders/TerrainShader.h"
#include "../Terrains/Terrain.h"


class TerrainRenderer
{
public:
	TerrainRenderer(TerrainShader& shader, glm::mat4 projectionMatrix);
	void render(std::list<Terrain> terrains);
private:
	void bindTerrainModel(Terrain& terrain);
	void unbindTerrainModel();
	void renderTerrain(Terrain& terrain);

	TerrainShader _shader;
};

