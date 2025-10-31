#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "glad/glad.h"

#include "Shader.h"

struct Vertex {
	glm::vec4 color;
	glm::vec3 point;
};

struct Mesh {
	
public:
	Mesh(const std::vector<Vertex>& vertices, unsigned int nTriangles, ShaderClass shaderClass, int renderType = GL_TRIANGLES, int drawType = GL_STATIC_DRAW);

	glm::mat4 model;
	Shader shader;
	unsigned int vaoId;
	unsigned int vboPointsId;
	unsigned int vboColorsId;
	unsigned int nVertices;
	unsigned int nTriangles;
	int renderType;
};
