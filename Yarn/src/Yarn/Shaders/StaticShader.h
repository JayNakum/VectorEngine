#pragma once

#include "ShaderProgram.h"

class StaticShader : public ShaderProgram
{
public:
	StaticShader();
	void bindAttributes() override;
};
