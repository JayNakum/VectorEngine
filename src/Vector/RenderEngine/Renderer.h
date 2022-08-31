#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <unordered_map>
#include <vector>

#include "../Shaders/StaticShader.h"
#include "../Models/TexturedModel.h"
#include "../Entities/Entity.h"


struct tmCompare
{
public:
	bool operator()(const TexturedModel t1, const TexturedModel& t2)
	{
		return &t1 == &t2;
	}
	/*
	std::size_t operator() (const TexturedModel& t1, const TexturedModel& t2) const {
		return std::hash<TexturedModel>()(t1) == std::hash<TexturedModel>()(t2);
	}
	*/
};


class Renderer
{
public:
	void prepare();
	void render(std::unordered_map<TexturedModel, std::vector<Entity>, tmCompare>& entities);

	Renderer(StaticShader& shader);
private:
	void bindTexturedModel(TexturedModel texturedModel);
	void unbindTexturedModel();
	void renderEntity(Entity& entity);

	StaticShader _shader;
};
