#include "Window.h"

#include <exception>

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void cursorPositionCallback(GLFWwindow* window, double x, double y);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

// Inizializza GLFW e crea una finestra ridimensionabile
Window::Window(const int width, const int height, const std::string& title)
	: open(true)
{
	if (!glfwInit()) {
		throw std::exception("Failed to initialize GLFW!");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if (!window) {
		glfwTerminate();
		throw std::exception("Failed to create Window!");
	}

	// Mantiene il rapporto dello schermo ogni volta che si ridimensiona la finestra
	glfwSetWindowAspectRatio(window, width, height);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		throw std::exception("Failed to load opengl function pointers!");
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Window::~Window() {
	glfwTerminate();
}

void Window::render() {

	glfwSwapBuffers(window);
}

void Window::clear() {
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		input.pressKey(scancode);
	}
	else if (action == GLFW_RELEASE) {
		input.releaseKey(scancode);
	}
}

void cursorPositionCallback(GLFWwindow* window, double x, double y) {

}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {

}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	if (height == 0) height = 1;

	glViewport(0, 0, width, height);
}
