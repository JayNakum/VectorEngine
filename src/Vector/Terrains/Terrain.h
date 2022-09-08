#pragma once

#include <list>

#include "../Models/RawModel.h"
#include "../Textures/ModelTexture.h"
#include "../RenderEngine/Loader.h"

class Terrain
{
public:
	Terrain(int gridX, int gridZ, Loader& loader, ModelTexture& texture);

	inline float getX() const { return _x; }
	inline float getZ() const { return _z; }
	inline RawModel getModel() const { return _model; }
	inline ModelTexture getTexture() const { return _texture; }

private:

	RawModel generateTerrain(Loader& loader);

	float _x, _z;
	RawModel _model;
	ModelTexture _texture;

	const float _SIZE = 800;
	const float _VERTEX_COUNT = 128;
};

