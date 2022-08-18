#include "Loader.h"

#include "../Log.h"

#include <stb_image/stb_image.h>

RawModel Loader::loadToVAO(float vertices[], unsigned int vertCount, unsigned int indices[], unsigned int indCount, float textureCoords[], unsigned int texCount)
{
    unsigned int vaoID = createVAO();
    bindIndicesBuffer(indices, indCount);
    storeDataInAttributeList(0, 3, vertices, vertCount);
    storeDataInAttributeList(1, 2, textureCoords, texCount);
    unbindVAO();
    return RawModel(vaoID, vertCount);
}

unsigned int Loader::loadTexture(const std::string& fileName, bool repeat)
{
    unsigned int textureID;
    int width, height, numComponents;

    stbi_uc* imageData = stbi_load(("res\\textures\\" + fileName + ".png").c_str(), &width, &height, &numComponents, 4);

    if (imageData == NULL)
    {
        ERROR("Texture loading failed");
        ERROR(fileName);
    }

    glGenTextures(1, &textureID);

    _TEXTUREs.push_back(textureID);

    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (!repeat)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    
    stbi_image_free(imageData);

    return textureID;
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

void Loader::storeDataInAttributeList(unsigned int attributeNumber, int coordinateSize, float data[], unsigned int count)
{
    unsigned int vboID;
    glGenBuffers(1, &vboID);
    _VBOs.push_back(vboID);

    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data) * count, data, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Loader::Loader()
{
    _VAOs.clear();
    _VBOs.clear();
    _TEXTUREs.clear();
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

    while (_TEXTUREs.size() > 0)
    {
        glDeleteTextures(1, &_TEXTUREs.back());
        _TEXTUREs.pop_back();
    }
}
