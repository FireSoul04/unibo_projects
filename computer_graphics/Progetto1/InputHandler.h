#pragma once

#include <GLFW/glfw3.h>

constexpr int MAX_KEYS = GLFW_KEY_LAST;

class InputHandler {

public:
	InputHandler();

	bool isKeyPressed(int scancode);
	bool isKeyPressedOnce(int scancode);

	void pressKey(int scancode);
	void releaseKey(int scancode);

private:
	struct Key {
		int scancode;
		bool alreadyPressed;
	};

	bool keyPressed[MAX_KEYS];
	Key keys[MAX_KEYS];
};
