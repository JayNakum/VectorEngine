#pragma once

#include <glm/glm.hpp>

#include "../Models/TexturedModel.h"

class Entity
{
public:
	Entity(TexturedModel& model, glm::vec3 position, float rotX, float rotY, float rotZ, float scale);

	void changePosition(float dx, float dy, float dz);
	void changeRotation(float dx, float dy, float dz);

	inline TexturedModel getModel() const { return _model; }
	inline void setModel(TexturedModel& model) { _model = model; }

	inline glm::vec3 getPosition() const { return _position; }
	inline void setPosition(glm::vec3& position) { _position = position; }
	
	inline float getRotationX() const { return _rotX; }
	inline void setRotationX(float rotation) { _rotX = rotation; }

	inline float getRotationY() const { return _rotY; }
	inline void setRotationY(float rotation) { _rotY = rotation; }

	inline float getRotationZ() const { return _rotZ; }
	inline void setRotationZ(float rotation) { _rotZ = rotation; }
	
	inline float getScale() const { return _scale; }
	inline void setScale(float scale) { _scale = scale; }

private:
	TexturedModel _model;
	glm::vec3 _position;
	float _rotX, _rotY, _rotZ;
	float _scale;
};
