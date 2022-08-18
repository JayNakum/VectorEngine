#include "StaticShader.h"

StaticShader::StaticShader()
	: ShaderProgram("res\\shaders\\vertex.shader", "res\\shaders\\fragment.shader") {}

void StaticShader::bindAttributes()
{
	bindAttribute(0, "position");
	bindAttribute(1, "textureCoords");
}