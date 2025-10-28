#include "InputHandler.h"

InputHandler::InputHandler() {
	for (int scancode = 0; scancode < MAX_KEYS; scancode++) {
		Key key;
		key.scancode = scancode;
		key.alreadyPressed = false;
		keys[scancode] = key;
		keyPressed[scancode] = false;
	}
}

bool InputHandler::isKeyPressed(int scancode) {
	return keyPressed[scancode];
}

bool InputHandler::isKeyPressedOnce(int scancode) {
	Key& key = keys[scancode];
	bool keyPressed = false;
	if (!key.alreadyPressed && isKeyPressed(scancode)) {
		key.alreadyPressed = true;
		keyPressed = true;
	} else if (!isKeyPressed(scancode)) {
		key.alreadyPressed = false;
	}
	return keyPressed;
}

void InputHandler::pressKey(int scancode) {
	keyPressed[scancode] = true;
}

void InputHandler::releaseKey(int scancode) {
	keyPressed[scancode] = false;
}
