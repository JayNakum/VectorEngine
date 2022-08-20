#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	Camera();

	void move();

	inline glm::vec3 getPosition() const { return _position; }
	inline float getPitch() const { return _pitch; }
	inline float getYaw() const { return _yaw; }
	inline float getRoll() const { return _roll; }

private:
	glm::vec3 _position;
	float _pitch;
	float _yaw;
	float _roll;
	bool _wireframe = false;
	float _speed = 0.1f;
};
