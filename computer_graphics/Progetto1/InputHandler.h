#pragma once

#include <GLFW/glfw3.h>

#include <functional>

class InputHandler {

public:
	enum Action {
		MOVE_LEFT,
		MOVE_RIGHT,
		MOVE_UP,
		MOVE_DOWN,
		SHOOT,
		// TURBO, // FORSE
		QUIT,

		ACTION_COUNT
	};

	InputHandler();

	bool isKeyPressed(Action scancode);
	bool isKeyPressedOnce(Action scancode);

	void pressKey(int scancode);
	void releaseKey(int scancode);

private:
	struct Key {
		int action;
		bool alreadyPressed;
	};

	bool keyPressed[ACTION_COUNT];
	Key keys[ACTION_COUNT];
};
