#include "GameObject.h"

GameObject::GameObject(std::vector<Mesh> meshes, glm::vec3 position) {
	this->meshes = meshes;
	this->position = position;
	rotationAngles = glm::vec3(0);
	scaleFactors = glm::vec3(0);
	transformation = glm::mat4(1.0f);
}

void GameObject::update(float dt) {
	transformation = glm::translate(glm::mat4(1.0f), position);
	transformation = glm::rotate(transformation, rotationAngles.x, glm::vec3(1.0f, 0.0f, 0.0f));
	transformation = glm::rotate(transformation, rotationAngles.y, glm::vec3(0.0f, 1.0f, 0.0f));
	transformation = glm::rotate(transformation, rotationAngles.z, glm::vec3(0.0f, 0.0f, 1.0f));
	transformation = glm::scale(transformation, scaleFactors);
}

void GameObject::translate(glm::vec3 newPosition) {
	position = newPosition;
}

void GameObject::rotate(glm::vec3 angles) {
	rotationAngles = angles;
}

void GameObject::scale(glm::vec3 factors) {
	scaleFactors = factors;
}
