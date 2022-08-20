#include "ModelTexture.h"

ModelTexture::ModelTexture(unsigned int id)
	: _textureID(id) {}

void ModelTexture::setShineDamper(float shineDamper)
{
	_shineDamper = shineDamper;
}

void ModelTexture::setReflectivity(float reflectivity)
{
	_reflectivity = reflectivity;
}
