#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Mesh.h"

class GameObject {
	
public:
	GameObject(std::vector<Mesh> meshes, glm::vec3 position = glm::vec3(0));
	
	// Fare distruttore
	
	void update(float dt);

	void translate(glm::vec3 newPosition);
	void rotate(glm::vec3 angles);
	void scale(glm::vec3 factors);

private:
	glm::mat4 transformation;
	glm::vec3 position;
	glm::vec3 rotationAngles;
	glm::vec3 scaleFactors;
	std::vector<Mesh> meshes;
};
