#pragma once

#include "Renderer.h"

class MasterRenderer
{
public:
	MasterRenderer(float aspectRatio);
	virtual ~MasterRenderer();

	void render(Light& light, Camera& camera);
	void processEntity(Entity& entity);
private:
	const float _FOV = 70;
	const float _NEAR_PLANE = 0.1f;
	const float _FAR_PLANE = 1000;
	StaticShader _shader;
	Renderer _renderer;

	std::unordered_map<TexturedModel, std::vector<Entity>, tmCompare> _entities;
};
