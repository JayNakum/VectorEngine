#pragma once

#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <glm/glm.hpp>

#include <list>
#include <vector>
#include <string>

#include "../Models/RawModel.h"

class Loader
{
public:
	Loader();

	RawModel loadToVAO(std::list<glm::vec3> vertices, std::list<glm::vec2> textures, std::list<glm::vec3> normals, std::vector<int> indices);
	unsigned int loadTexture(const std::string& fileName, bool repeat);
	void unbindVAO();

	virtual ~Loader();
private:
	unsigned int createVAO();
	void storeDataInAttributeList(unsigned int attribNumber, int size, void* data, int count);
	void bindIndicesBuffer(int* indices, int count);

	std::list<unsigned int> _VAOs;
	std::list<unsigned int> _VBOs;
	std::list<unsigned int> _TEXTUREs;
};