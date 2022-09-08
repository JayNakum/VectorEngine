#include "ShaderProgram.h"

#include "../Log.h"


#include <stdio.h>


unsigned int ShaderProgram::loadShader(const char* shaderPath, int type)
{
	// Open the file as read only
	FILE* file;
	if (fopen_s(&file, shaderPath, "r") != 0)
	{
		printf("Failed to open: %s\n", shaderPath);
	}

	// Create temp variables
	std::string source;
	char buffer[1024];
	while (fgets(buffer, 1024, file) != NULL)
	{
		source.append(buffer);
	}
	fclose(file);

	// Create shader ID
	GLuint shaderID = glCreateShader(type);

	// Prepare source for OpenGL
	const GLchar* sourceStrings[1];
	GLint sourceLengths[1];
	sourceStrings[0] = source.c_str();
	sourceLengths[0] = source.length();

	// Load source to OpenGL and compile
	glShaderSource(shaderID, 1, sourceStrings, sourceLengths);
	glCompileShader(shaderID);

	// Check compile status
	GLint status;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		// Get info log length
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		// Get the info log
		GLchar* infoLog = new GLchar[infoLogLength];
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, infoLog);
		printf("ERROR: could not compile shader \n%s\n", infoLog);
		// Delete the array
		delete[] infoLog;
	}

	return shaderID;
}
ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath)
{
    _vertexShaderID = loadShader(vertexShaderPath, GL_VERTEX_SHADER);
    _fragmentShaderID = loadShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

    _programID = glCreateProgram();
    glAttachShader(_programID, _vertexShaderID);
    glAttachShader(_programID, _fragmentShaderID);

    bindAttributes();
    
    glLinkProgram(_programID);
    glValidateProgram(_programID);

    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(_programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(_programID, 1024, NULL, infoLog);
        ERROR("SHADER PROGRAM LINKING ERROR");
        TRACE(infoLog);
    }

    getAllUniformLocations();
}

ShaderProgram::~ShaderProgram()
{
    cleanUp();
}

void ShaderProgram::start()
{
    glUseProgram(_programID);
}

void ShaderProgram::stop()
{
    glUseProgram(0);
}

void ShaderProgram::cleanUp()
{
    stop();
    glDetachShader(_programID, _vertexShaderID);
    glDetachShader(_programID, _fragmentShaderID);

    glDeleteShader(_vertexShaderID);
    glDeleteShader(_fragmentShaderID);

    glDeleteProgram(_programID);
}

void ShaderProgram::bindAttributes() {}

void ShaderProgram::bindAttribute(unsigned int attribute, const char* variableName)
{
    glBindAttribLocation(_programID, attribute, variableName);
}

void ShaderProgram::getAllUniformLocations() {}

int ShaderProgram::getUniformLocation(const char* uniformName)
{
    return glGetUniformLocation(_programID, uniformName);
}

void ShaderProgram::loadFloat(int location, float value)
{
    glUniform1f(location, value);
}

void ShaderProgram::loadVector(int location, glm::vec3 vector)
{
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void ShaderProgram::loadBoolean(int location, bool value)
{
    float toLoad = 0.0f;
    if (value)
        toLoad = 1.0f;
    glUniform1f(location, toLoad);
}

void ShaderProgram::loadMatrix(int location, glm::mat4 matrix)
{
    glUniformMatrix4fv(location, 1, false, &matrix[0][0]);
}

/*
unsigned int ShaderProgram::loadShader(const char* shaderPath, int type)
{
    std::string shaderCode;
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        shaderFile.open(shaderPath);

        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();

        shaderFile.close();

        shaderCode = shaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        ERROR("SHADER FILE NOT READ SUCCESFULLY");
        TRACE(e.what());
    }
    const char* src = shaderCode.c_str();

    unsigned int id;
    id = glCreateShader(type);

    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);
    
    GLint success;
    GLchar infoLog[1024];
    
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(id, 1024, NULL, infoLog);
        ERROR("SHADER COMPILATION ERROR");
        TRACE(infoLog);
    }

    return id;

}
*/