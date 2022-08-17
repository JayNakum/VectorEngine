#include "Loader.h"

RawModel Loader::loadToVAO(float vertices[], unsigned int vertCount, unsigned int indices[], unsigned int indCount)
{
    unsigned int vaoID = createVAO();
    bindIndicesBuffer(indices, indCount);
    storeDataInAttributeList(0, vertices, vertCount);
    unbindVAO();
    return RawModel(vaoID, vertCount);
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

void Loader::bindIndicesBuffer(unsigned int indices[], unsigned int count)
{
    unsigned int vboID;
    glGenBuffers(1, &vboID);
    _VBOs.push_back(vboID);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * count, indices, GL_STATIC_DRAW);
}

void Loader::storeDataInAttributeList(unsigned int attributeNumber, float data[], unsigned int count)
{
    unsigned int vboID;
    glGenBuffers(1, &vboID);
    _VBOs.push_back(vboID);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data) * count, data, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Loader::Loader()
{
    _VAOs.clear();
    _VBOs.clear();
}

Loader::~Loader()
{
    cleanUp();
}

void Loader::cleanUp()
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
}
