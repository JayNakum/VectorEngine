#pragma once

#include "EntityRenderer.h"

#include "../Shaders/TerrainShader.h"
#include "TerrainRenderer.h"

class MasterRenderer
{
public:
	MasterRenderer(float aspectRatio);
	virtual ~MasterRenderer();

	void prepare();
	void render(Light& light, Camera& camera);
	void processEntity(Entity& entity);
	void processTerrain(Terrain& terrain);
private:
	const float _FOV = 70;
	const float _NEAR_PLANE = 0.1f;
	const float _FAR_PLANE = 1000;
	glm::mat4 _projectionMatrix;

	StaticShader _shader;
	EntityRenderer _entityRenderer;
	TerrainShader _terrainShader;
	TerrainRenderer _terrainRenderer;

	std::map<TexturedModel, std::list<Entity>, tmCompare> _entities;
	std::list<Terrain> _terrains;
};
