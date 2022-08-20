#pragma once

#include "ShaderProgram.h"

#include "../Entities/Camera.h"
#include "../Entities/Light.h"

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	void bindAttributes() override;
	void getAllUniformLocations() override;
	
	void loadTransformationMatrix(glm::mat4 matrix);
	void loadViewMatrix(Camera& camera);
	void loadProjectionMatrix(glm::mat4 matrix);

	void loadLight(Light& light);
private:
	int _location_transformationMatrix = 0;
	int _location_projectionMatrix = 0;
	int _location_viewMatrix = 0;

	int _location_lightPosition = 0;
	int _location_lightColor = 0;
};
