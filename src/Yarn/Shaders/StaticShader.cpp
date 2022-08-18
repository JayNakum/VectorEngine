#include "StaticShader.h"

#include "../Toolbox/Maths.h"

StaticShader::StaticShader()
	: ShaderProgram("res\\shaders\\vertex.shader", "res\\shaders\\fragment.shader") 
{
	bindAttributes();
	getAllUniformLocations();
}

void StaticShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
}

void StaticShader::getAllUniformLocations()
{
	_location_transformationMatrix = getUniformLocation("transformationMatrix");
	_location_projectionMatrix = getUniformLocation("projectionMatrix");
	_location_viewMatrix = getUniformLocation("viewMatrix");
}

void StaticShader::loadTransformationMatrix(glm::mat4 matrix)
{
	loadMatrix(_location_transformationMatrix, matrix);
}

void StaticShader::loadViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix = Maths::createViewMatrix(camera);
	loadMatrix(_location_viewMatrix, viewMatrix);
}

void StaticShader::loadProjectionMatrix(glm::mat4 matrix)
{
	loadMatrix(_location_projectionMatrix, matrix);
}
