#include "Loader.h"

#include "../Log.h"

RawModel Loader::loadToVAO(float* vertices, int* indices, float* texCoords, float* normals, int vertCount, int indCount, int texCount, int normalsCount)
{
	unsigned int vaoID = createVAO();
	bindIndicesBuffer(indices, indCount);
	
	storeDataInAttributeList(0, 3, vertices, vertCount);
	storeDataInAttributeList(1, 2, texCoords, texCount);
	storeDataInAttributeList(2, 3, normals, normalsCount);
	
	unbindVAO();
	return RawModel(vaoID, indCount);
}


unsigned int Loader::loadTexture(const std::string& fileName)
{
	unsigned int texture;
	int width, height, numComponents;
	
	stbi_uc* imageData = stbi_load(("res\\textures\\" + fileName + ".png").c_str(), &width, &height, &numComponents, 4);

	if (imageData == NULL)
	{
		ERROR("FAILED TO LOAD TEXTURE");
	    ERROR(fileName);
	}

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);

	_TEXTUREs.push_back(texture);

	stbi_image_free(imageData);

	return texture;
}

unsigned int Loader::createVAO()
{
	unsigned int vaoID;
	
	glGenVertexArrays(1, &vaoID);
	
	_VAOs.push_back(vaoID);
	
	glBindVertexArray(vaoID);
	return vaoID;
}

void Loader::unbindVAO()
{
	glBindVertexArray(0);
}

void Loader::storeDataInAttributeList(unsigned int attribNumber, int size, float* data, int count)
{
	unsigned int vboID;
	
	glGenBuffers(1, &vboID);
	
	_VBOs.push_back(vboID);
	
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count, data, GL_STATIC_DRAW);
	
	glVertexAttribPointer(attribNumber, size, GL_FLOAT, GL_FALSE, 0, nullptr);
}


void Loader::bindIndicesBuffer(int* indices, int count)
{
	unsigned int vboID;
	
	glGenBuffers(1, &vboID);
	
	_VBOs.push_back(vboID);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);
	
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * count, indices, GL_STATIC_DRAW);
}

Loader::Loader()
{
	_VAOs.clear();
	_VBOs.clear();
	_TEXTUREs.clear();
}

Loader::~Loader()
{
	while (_VBOs.size() > 0)
	{
		glDeleteBuffers(1, &_VBOs.back());
		_VBOs.pop_back();
	}

	while (_VAOs.size() > 0)
	{
		glDeleteVertexArrays(1, &_VAOs.back());
		_VAOs.pop_back();
	}

	while (_TEXTUREs.size() > 0)
	{
		glDeleteTextures(1, &_TEXTUREs.back());
		_TEXTUREs.pop_back();
	}
}
