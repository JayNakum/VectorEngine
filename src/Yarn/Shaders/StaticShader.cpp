#include "StaticShader.h"

StaticShader::StaticShader()
	: ShaderProgram("res\\shaders\\vertex.shader", "res\\shaders\\fragment.shader") {}

void StaticShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
}

void StaticShader::getAllUniformLocations()
{
	_location_transformationMatrix = getUniformLocation("transformationMatrix");
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix)
{
	loadMatrix(_location_transformationMatrix, matrix);
}
