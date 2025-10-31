#pragma once

#include "Scene.h"
#include "Window.h"

class Game {
	
public:
	Game(const int width, const int height);

	void run();
	void update(float dt);

private:
	int width;
	int height;
	
	Window window;
	Scene scene;
};
