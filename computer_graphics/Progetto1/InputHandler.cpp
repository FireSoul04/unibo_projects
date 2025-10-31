#include "InputHandler.h"

InputHandler::InputHandler() {
	for (int action = 0; action < ACTION_COUNT; action++) {
		Key key;
		key.action = action;
		key.alreadyPressed = false;
		keys[action] = key;
		keyPressed[action] = false;
	}
}

bool InputHandler::isKeyPressed(Action action) {
	return keyPressed[action];
}

bool InputHandler::isKeyPressedOnce(Action action) {
	Key& key = keys[action];
	bool keyPressed = false;
	if (!key.alreadyPressed && isKeyPressed(action)) {
		key.alreadyPressed = true;
		keyPressed = true;
	} else if (!isKeyPressed(action)) {
		key.alreadyPressed = false;
	}
	return keyPressed;
}

void InputHandler::pressKey(int button) {
	if (button == GLFW_KEY_LEFT || button == GLFW_KEY_A) {
		keyPressed[MOVE_LEFT] = true;
	} else if (button == GLFW_KEY_RIGHT || button == GLFW_KEY_D) {
		keyPressed[MOVE_RIGHT] = true;
	} else if (button == GLFW_KEY_UP || button == GLFW_KEY_W) {
		keyPressed[MOVE_UP] = true;
	} else if (button == GLFW_KEY_DOWN || button == GLFW_KEY_S) {
		keyPressed[MOVE_DOWN] = true;
	} else if (button == GLFW_KEY_SPACE || button == GLFW_MOUSE_BUTTON_1) {
		keyPressed[SHOOT] = true;
	}
	// else if (button == GLFW_KEY_SHIFT) {
	//	keyPressed[TURBO] = true;
	// }
	else if (button == GLFW_KEY_ESCAPE) {
		keyPressed[QUIT] = true;
	}
}

void InputHandler::releaseKey(int button) {
	if (button == GLFW_KEY_LEFT || button == GLFW_KEY_A) {
		keyPressed[MOVE_LEFT] = false;
	} else if (button == GLFW_KEY_RIGHT || button == GLFW_KEY_D) {
		keyPressed[MOVE_RIGHT] = false;
	} else if (button == GLFW_KEY_UP || button == GLFW_KEY_W) {
		keyPressed[MOVE_UP] = false;
	} else if (button == GLFW_KEY_DOWN || button == GLFW_KEY_S) {
		keyPressed[MOVE_DOWN] = false;
	} else if (button == GLFW_KEY_SPACE || button == GLFW_MOUSE_BUTTON_1) {
		keyPressed[SHOOT] = false;
	}
	// else if (button == GLFW_KEY_SHIFT) {
	//	keyPressed[TURBO] = false;
	// }
	else if (button == GLFW_KEY_ESCAPE) {
		keyPressed[QUIT] = false;
	}
}
