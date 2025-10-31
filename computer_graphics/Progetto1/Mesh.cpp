#include "Mesh.h"

#include <glad/glad.h>

Mesh::Mesh(const std::vector<Vertex>& vertices, unsigned int nTriangles, ShaderClass shaderClass, int renderType, int drawType)
	: shader(shaderClass)
{
	model = glm::mat4(1.0f);
	vaoId = 0;
	vboColorsId = 0;
	vboPointsId = 0;
	nVertices = vertices.size();
	this->renderType = renderType;
	this->nTriangles = nTriangles;

	std::vector<glm::vec3> points;
	std::vector<glm::vec4> colors;
	for (const Vertex& v : vertices) {
		points.push_back(v.point);
		colors.push_back(v.color);
	}

	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	glGenBuffers(1, &vboPointsId);
	glBindBuffer(GL_ARRAY_BUFFER, vboPointsId);
	glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(glm::vec3), points.data(), drawType);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glGenBuffers(1, &vboColorsId);
	glBindBuffer(GL_ARRAY_BUFFER, vboColorsId);
	glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(glm::vec4), colors.data(), drawType);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
}
