#pragma once

#include <glad/glad.h>

class ShaderProgram 
{
public:
	ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	~ShaderProgram();

	void start();
	void stop();
	void cleanUp();

protected:
	virtual void bindAttributes() = 0;
	void bindAttribute(unsigned int attribute, const char* variableName);

private:
	unsigned int loadShader(const char* shaderPath, int type);

	unsigned int _programID;
	unsigned int _vertexShaderID;
	unsigned int _fragmentShaderID;

};