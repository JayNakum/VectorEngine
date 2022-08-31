#pragma once

#include "RawModel.h"

#include "../Textures/ModelTexture.h"

class TexturedModel
{
public:
	TexturedModel(RawModel& model, ModelTexture& texture);

	inline RawModel getRawModel() const { return _rawModel; }
	inline ModelTexture getTexture() const { return _texture; }

private:
	RawModel _rawModel;
	ModelTexture _texture;
};
