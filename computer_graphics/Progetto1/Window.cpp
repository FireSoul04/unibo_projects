#include "Window.h"

#include <exception>
#include <glm/gtc/matrix_transform.hpp>

Window* myWindow;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		myWindow->input.pressKey(key);
	} else if (action == GLFW_RELEASE) {
		myWindow->input.releaseKey(key);
	}
}

void cursorPositionCallback(GLFWwindow* window, double x, double y) {
	myWindow->mousePosition = glm::vec2(x, y);
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	if (action == GLFW_PRESS) {
		myWindow->input.pressKey(button);
	} else if (action == GLFW_RELEASE) {
		myWindow->input.releaseKey(button);
	}
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Inizializza GLFW e crea una finestra ridimensionabile
Window::Window(const int width, const int height, const std::string& title) {
	input = InputHandler();
	mousePosition = glm::vec2(0);
	myWindow = this;
	proj = glm::ortho(0.0f, (float) width, 0.0f, (float) height);

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

	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwDestroyWindow(window);
		glfwTerminate();
		throw std::exception("Failed to load opengl function pointers!");
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

Window::~Window() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void Window::render(std::vector<Mesh*> meshes) {
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (Mesh* m : meshes) {
		m->shader.use(proj, m->model);
		glBindVertexArray(m->vaoId);
		glDrawArrays(m->renderType, 0, m->nVertices);
	}

	glfwSwapBuffers(window);
	glfwPollEvents();

	if (input.isKeyPressedOnce(InputHandler::QUIT)) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

bool Window::shouldClose() {
	return glfwWindowShouldClose(window);
}

float Window::getTime() {
	return glfwGetTime();
}

bool Window::isActionPressed(InputHandler::Action action) {
	return input.isKeyPressed(action);
}

bool Window::isActionPressedOnce(InputHandler::Action action) {
	return input.isKeyPressedOnce(action);
}
