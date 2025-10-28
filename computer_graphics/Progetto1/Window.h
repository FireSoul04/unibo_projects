#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "InputHandler.h"

class Window {

public:
	Window(const int width, const int height, const std::string& title);
	~Window();

	void render();
	void clear();

private:
	GLFWwindow* window;
	InputHandler input;
	bool open;
};
