#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <exception>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(ShaderClass shaderClass) {
	int success;
	char infoLog[512];
	std::string vertexFilename = "vertex.glsl";
	std::string fragmentFilename = "fragment.glsl";

	const std::string vertexShaderSource = readShaderSource(vertexFilename);
	char const* vShaderSource[] = {vertexShaderSource.c_str()};
	unsigned int vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, vShaderSource, nullptr);
	glCompileShader(vertexShaderID);

	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
		const std::string log = std::string("Vertex shader compilation failed: ").append(infoLog).append("\n");
		throw std::exception(log.c_str());
	}
	const std::string fragmentShaderSource = readShaderSource(fragmentFilename);
	char const* fShaderSource[] = {fragmentShaderSource.c_str()};
	unsigned int fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, fShaderSource, nullptr);
	glCompileShader(fragmentShaderID);

	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		const std::string log = std::string("Fragment shader compilation failed: ").append(infoLog).append("\n");
		throw std::exception(log.c_str());
	}
	programId = glCreateProgram();

	glAttachShader(programId, vertexShaderID);
	glAttachShader(programId, fragmentShaderID);
	glLinkProgram(programId);

	idProj = glGetUniformLocation(programId, "projection");
	idModel = glGetUniformLocation(programId, "model");
}

#pragma warning(disable : 4996)
const std::string Shader::readShaderSource(const std::string& filename) {
	FILE* file = fopen(filename.c_str(), "rb");
	if (!file) {
		std::string filelog = std::string("Shader file not found: ").append(filename);
		throw std::exception(filelog.c_str());
	}

	fseek(file, 0L, SEEK_END);
	long size = ftell(file);

	fseek(file, 0L, SEEK_SET);
	char* buf = new char[size + 1];
	fread(buf, 1, size, file);

	buf[size] = '\0';
	fclose(file);

	const std::string shaderSource = std::string(buf);
	delete[] buf;

	return shaderSource;
}

void Shader::use(glm::mat4& proj, glm::mat4& model) {
	glUseProgram(programId);

	glUniformMatrix4fv(idProj, 1, GL_FALSE, glm::value_ptr(proj));
	glUniformMatrix4fv(idModel, 1, GL_FALSE, glm::value_ptr(model));
}
