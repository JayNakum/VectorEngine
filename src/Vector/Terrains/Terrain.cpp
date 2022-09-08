#include "Terrain.h"

#include <glm/glm.hpp>

Terrain::Terrain(int gridX, int gridZ, Loader& loader, ModelTexture& texture)
	: _x(gridX * _SIZE), _z(gridZ * _SIZE), _model(generateTerrain(loader)), _texture(texture)
{
}

RawModel Terrain::generateTerrain(Loader& loader)
{
	int count = _VERTEX_COUNT * _VERTEX_COUNT;
	std::list<glm::vec3> vertices(count), normals(count);
	std::list<glm::vec2> textureCoords(count);
	std::vector<int> indices(6 * (_VERTEX_COUNT - 1) * _VERTEX_COUNT);
	int vertexPointer = 0;
	for (int i = 0; i < _VERTEX_COUNT; i++)
	{
		for (int j = 0; j < _VERTEX_COUNT; j++)
		{
			vertices[vertexPointer] = glm::vec3(
				(float)j / ((float)_VERTEX_COUNT - 1) * _SIZE,
				0,
				(float)i / ((float)_VERTEX_COUNT - 1) * _SIZE);
			normals[vertexPointer] = glm::vec3(0, 1, 0);
			textureCoords[vertexPointer] = glm::vec2(
				(float)j / ((float)_VERTEX_COUNT - 1),
				(float)i / ((float)_VERTEX_COUNT - 1));
			vertexPointer++;
		}
	}
	int pointer = 0;
	for (int gz = 0; gz < _VERTEX_COUNT - 1; gz++)
	{
		for (int gx = 0; gx < _VERTEX_COUNT - 1; gx++)
		{
			int topLeft = (gz * _VERTEX_COUNT) + gx;
			int topRight = topLeft + 1;
			int bottomLeft = ((gz + 1) * _VERTEX_COUNT) + gx;
			int bottomRight = bottomLeft + 1;
			indices[pointer++] = topLeft;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = topRight;
			indices[pointer++] = topRight;
			indices[pointer++] = bottomLeft;
			indices[pointer++] = bottomRight;
		}
	}
	return loader.loadToVAO(vertices, textureCoords, normals, indices);
}
