#include "Camera.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

Camera::Camera()
	: _position(glm::vec3(0, 0, 0)), _pitch(0), _yaw(0), _roll(0) {}

void Camera::move()
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
		_position.z -= _speed;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
		_position.z += _speed;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
		_position.x -= _speed;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
		_position.x += _speed;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		_position.y -= _speed;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_SPACE) == GLFW_PRESS)
		_position.y += _speed;

	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_F6) == GLFW_PRESS)
	{
		if (_wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		_wireframe = !_wireframe;
	}
}
