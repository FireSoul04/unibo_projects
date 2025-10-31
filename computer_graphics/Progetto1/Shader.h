#pragma once

#include <string>
#include <glm/glm.hpp>

enum ShaderClass {
	BACKGROUND,
	PLAYER,
	ASTEROID
};

class Shader {

public:
	Shader(ShaderClass shaderClass);
	// Aggiungere distruttore

	const std::string readShaderSource(const std::string& filename);
	void use(glm::mat4& proj, glm::mat4& model);

private:
	unsigned int programId;
	unsigned int idProj;
	unsigned int idModel;
};
