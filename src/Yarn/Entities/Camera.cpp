#include "Camera.h"
#include <GLFW\glfw3.h>

Camera::Camera()
	: _position(glm::vec3(0, 0, 0)), _pitch(0), _yaw(0), _roll(0) {}

void Camera::move()
{
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS)
		_position.z -= 0.02f;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS)
		_position.z += 0.02f;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_A) == GLFW_PRESS)
		_position.x -= 0.02f;
	if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_D) == GLFW_PRESS)
		_position.x += 0.02f;
}
