#pragma once

#include <vector>

#include "GameObject.h"

class Scene {

public:
	Scene();

private:
	std::vector<GameObject> gameObjects;
};
