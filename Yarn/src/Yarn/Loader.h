#pragma once

#include <glad/glad.h>

#include <list>

#include "RawModel.h"

class Loader
{
public:
	RawModel loadToVAO(float vertices[], unsigned int vertCount, unsigned int indices[], unsigned int indCount);
	void cleanUp();

	Loader();
	virtual ~Loader();
private:
	unsigned int createVAO();
	void unbindVAO();
	void bindIndicesBuffer(unsigned int indices[], unsigned int count);
	void storeDataInAttributeList(unsigned int attributeNumber, float data[], unsigned int count);

	std::list<unsigned int> _VAOs;
	std::list<unsigned int> _VBOs;
};
