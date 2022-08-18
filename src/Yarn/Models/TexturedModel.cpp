#include "TexturedModel.h"

TexturedModel::TexturedModel(RawModel& model, ModelTexture& texture)
	: _rawModel(model), _texture(texture) {}
