#pragma once

#include <glad/glad.h>

#include <vector>
#include <string>

#include "../Models/RawModel.h"

class Loader
{
public:
	Loader();
	virtual ~Loader();

	RawModel LoadToVAO(float* vertices, int* indices, float* texCoords, int vertCount, int indCount, int texCount);
	GLuint LoadTexture(const std::string& fileName);
	inline void UnbindVAO() { glBindVertexArray(0); }
private:
	std::vector<GLuint> m_vaos;
	std::vector<GLuint> m_vbos;
	std::vector<GLuint> m_textures;
	GLuint CreateVAO();
	void StoreDataInAttributeList(GLuint attribNumber, int size, float* data, int& count);
	void BindIndicesBuffer(int* indices, int& count);
};