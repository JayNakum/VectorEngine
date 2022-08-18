#include "Maths.h"

glm::mat4 Maths::createTransformation(glm::vec3 translation, float rx, float ry, float rz, float scale)
{
	glm::mat4 model = glm::mat4(1.0f);

	model = glm::translate(model, translation);

	model = glm::rotate(model, glm::radians(rx), glm::vec3(1, 0, 0));
	model = glm::rotate(model, glm::radians(ry), glm::vec3(0, 1, 0));
	model = glm::rotate(model, glm::radians(rz), glm::vec3(0, 0, 1));

	model = glm::scale(model, glm::vec3(scale, scale, scale));

	return model;
}

glm::mat4 Maths::createViewMatrix(Camera& camera)
{
	glm::mat4 viewMatrix = glm::mat4(1.0f);
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getPitch()), glm::vec3(1, 0, 0));
	viewMatrix = glm::rotate(viewMatrix, glm::radians(camera.getYaw()), glm::vec3(0, 1, 0));

	glm::vec3 cameraPos = camera.getPosition();
	glm::vec3 negativeCameraPos = glm::vec3(-cameraPos.x, -cameraPos.y, -cameraPos.z);
	
	viewMatrix = glm::translate(viewMatrix, negativeCameraPos);

	return viewMatrix;
	// return glm::lookAt(camera.getPosition(), camera.getPosition() + glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));
}
