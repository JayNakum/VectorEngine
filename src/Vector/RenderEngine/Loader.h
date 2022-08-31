#pragma once

#include <glad/glad.h>
#include <stb_image/stb_image.h>

#include <vector>
#include <string>

#include "../Models/RawModel.h"

class Loader
{
public:
	Loader();

	RawModel loadToVAO(float* vertices, int* indices, float* texCoords, float* normals, int vertCount, int indCount, int texCount, int normalsCount);
	unsigned int loadTexture(const std::string& fileName);
	void unbindVAO();

	virtual ~Loader();
private:
	unsigned int createVAO();
	void storeDataInAttributeList(unsigned int attribNumber, int size, float* data, int count);
	void bindIndicesBuffer(int* indices, int count);

	std::vector<unsigned int> _VAOs;
	std::vector<unsigned int> _VBOs;
	std::vector<unsigned int> _TEXTUREs;
};