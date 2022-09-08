#include "MasterRenderer.h"

#include <glm\gtx\transform.hpp>
#include <iostream>

MasterRenderer::MasterRenderer(float aspectRatio)
	: _shader(), _projectionMatrix(glm::perspective(_FOV, aspectRatio, _NEAR_PLANE, _FAR_PLANE)), _entityRenderer(_shader, _projectionMatrix), _entities(), 
	_terrainShader(), _terrainRenderer(_terrainShader, _projectionMatrix)
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.3137f, 0.0f, 0.0f, 1.0f);
	glfwSwapInterval(1);
}


MasterRenderer::~MasterRenderer() 
{
	_shader.cleanUp();
	_terrainShader.cleanUp();
}

void MasterRenderer::prepare()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MasterRenderer::render(Light& light, Camera& camera)
{
	prepare();

	_shader.start();
	_shader.loadLight(light, 0.2f);
	_shader.loadViewMatrix(camera);
	_entityRenderer.render(_entities);
	_shader.stop();

	_terrainShader.start();
	_terrainShader.loadLight(light, 0.2f);
	_terrainShader.loadViewMatrix(camera);
	_terrainRenderer.render(_terrains);
	_terrainShader.stop();

	_terrains.clear();
	_entities.clear();
}

void MasterRenderer::processEntity(Entity& entity)
{
	TexturedModel texturedModel = entity.getModel();
	std::list<Entity> test;
	auto pair = std::make_pair(texturedModel, test);
	_entities.insert(pair);
	_entities.find(texturedModel)->second.push_back(entity);
}

void MasterRenderer::processTerrain(Terrain& terrain)
{
	_terrains.push_back(terrain);
}
