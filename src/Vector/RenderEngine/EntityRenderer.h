#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <map>
#include <list>

#include "../Shaders/StaticShader.h"
#include "../Models/TexturedModel.h"
#include "../Entities/Entity.h"


struct tmCompare
{
public:
	bool operator() (const TexturedModel& t1, const TexturedModel& t2) const
	{
		return ((t1.getRawModel().getVaoID() < t2.getRawModel().getVaoID()) ||
			(t1.getTexture().getID() < t2.getTexture().getID()));
	}
};


class EntityRenderer
{
public:
	void render(std::map<TexturedModel, std::list<Entity>, tmCompare>& entities);

	EntityRenderer(StaticShader& shader, glm::mat4 projectionMatrix);
private:
	void bindTexturedModel(TexturedModel texturedModel);
	void unbindTexturedModel();
	void renderEntity(Entity& entity);

	StaticShader _shader;
};
