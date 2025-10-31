#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>

#include "InputHandler.h"
#include "Mesh.h"

class Window {

public:
	Window(const int width, const int height, const std::string& title);
	~Window();

	void render(std::vector<Mesh*> meshes);

	bool shouldClose();
	float getTime();

	bool isActionPressed(InputHandler::Action action);
	bool isActionPressedOnce(InputHandler::Action action);

public:
	InputHandler input;
	glm::vec2 mousePosition;
	glm::mat4 proj;

private:
	GLFWwindow* window;
};
