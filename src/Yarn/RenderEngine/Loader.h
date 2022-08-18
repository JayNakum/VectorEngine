#pragma once

#include <glad/glad.h>

#include <string>
#include <list>

#include "../Models/RawModel.h"

class Loader
{
public:
	RawModel loadToVAO(float vertices[], unsigned int vertCount, unsigned int indices[], unsigned int indCount, float textureCoords[], unsigned int texCount);

	unsigned int loadTexture(const std::string& fileName, bool repeat = false);

	Loader();
	virtual ~Loader();
	void cleanUp();
private:
	unsigned int createVAO();
	void unbindVAO();
	void bindIndicesBuffer(unsigned int indices[], unsigned int count);
	void storeDataInAttributeList(unsigned int attributeNumber, int coordinateSize, float data[], unsigned int count);

	std::list<unsigned int> _VAOs;
	std::list<unsigned int> _VBOs;
	std::list<unsigned int> _TEXTUREs;
};
