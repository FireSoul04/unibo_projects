#pragma once

#include "Scene.h"
#include "Window.h"

class Game {
	
public:
	Game(const int width, const int height);
	~Game();

	void run();

private:
	const int width;
	const int height;
	
	Window window;
	Scene scene;
};
