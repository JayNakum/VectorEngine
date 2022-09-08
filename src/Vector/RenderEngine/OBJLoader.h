#pragma once

#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "Loader.h"

class OBJLoader
{
public:
	static RawModel loadObjModel(const std::string& fileName, Loader& loader);
private:
	static void processVertices(char* vertexData, std::vector<int>& indices, std::vector<glm::vec2>& tempTextures,
		std::list<glm::vec2>& textures, std::vector<glm::vec3>& tempNormals, std::list<glm::vec3>& normals);
};