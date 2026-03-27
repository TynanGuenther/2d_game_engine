#pragma once
#include <vector>
#include "GameObject.h"

class Scene {
    public:
	std::vector<GameObject> objects;
	
	void update(float deltaTime);
};
