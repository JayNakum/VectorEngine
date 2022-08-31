#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

class ShaderProgram 
{
public:
	ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	~ShaderProgram();

	void start();
	void stop();
	void cleanUp();

protected:
	virtual void bindAttributes();
	void bindAttribute(unsigned int attribute, const char* variableName);

	virtual void getAllUniformLocations();
	int getUniformLocation(const char* uniformName);

	void loadFloat(int location, float value);
	void loadVector(int location, glm::vec3 vector);
	void loadBoolean(int location, bool value);
	void loadMatrix(int location, glm::mat4 matrix);

private:
	unsigned int loadShader(const char* shaderPath, int type);

	unsigned int _programID;
	unsigned int _vertexShaderID;
	unsigned int _fragmentShaderID;

};