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
	bindAttribute(0, "normal");
}

void StaticShader::getAllUniformLocations()
{
	_location_transformationMatrix = getUniformLocation("transformationMatrix");
	_location_projectionMatrix = getUniformLocation("projectionMatrix");
	_location_viewMatrix = getUniformLocation("viewMatrix");

	_location_lightPosition = getUniformLocation("lightPosition");
	_location_lightColor = getUniformLocation("lightColor");
	_location_shineDamper = getUniformLocation("shineDamper");
	_location_reflectivity = getUniformLocation("reflectivity");
	_location_ambientLight = getUniformLocation("ambientLight");
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

void StaticShader::loadLight(Light& light, float ambientLight)
{
	loadVector(_location_lightPosition, light.getPosition());
	loadVector(_location_lightColor, light.getColor());
	loadFloat(_location_ambientLight, ambientLight);
}

void StaticShader::loadShineVariables(float damper, float reflectivity)
{
	loadFloat(_location_shineDamper, damper);
	loadFloat(_location_reflectivity, reflectivity);
}
