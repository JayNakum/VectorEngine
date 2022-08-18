#pragma once

#include "ShaderProgram.h"

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	void bindAttributes() override;
	void getAllUniformLocations() override;
	void loadTransformationMatrix(glm::mat4 matrix);
private:
	int _location_transformationMatrix;
};
