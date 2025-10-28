#include <iostream>

#include "Game.h"

constexpr int WIDTH = 1280;
constexpr int HEIGHT = 720;

int main(void) {
	Game game(WIDTH, HEIGHT);
	game.run();
}