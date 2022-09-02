#include "MasterRenderer.h"

#include <glm\gtx\transform.hpp>
#include <iostream>

MasterRenderer::MasterRenderer(float aspectRatio)
	: _shader(), _renderer(_shader), _entities()
{
	_shader.start();
	_shader.loadProjectionMatrix(glm::perspective(_FOV, aspectRatio, _NEAR_PLANE, _FAR_PLANE));
	_shader.stop();
}


MasterRenderer::~MasterRenderer() {}


void MasterRenderer::render(Light& light, Camera& camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	_shader.start();

	_shader.loadLight(light, 0.2f);
	_shader.loadViewMatrix(camera);

	_renderer.render(_entities);

	_shader.stop();
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