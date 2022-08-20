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
	void loadShineVariables(float damper, float reflectivity);

private:
	int _location_transformationMatrix = 0;
	int _location_projectionMatrix = 0;
	int _location_viewMatrix = 0;

	int _location_lightPosition = 0;
	int _location_lightColor = 0;
	int _location_shineDamper = 0;
	int _location_reflectivity = 0;
};
