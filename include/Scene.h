#pragma once
#include <vector>
#include <algorithm>
#include "GameObject.h"

class Scene {
    public:
	std::vector<GameObject> objects;
	
	GameObject& createObject();
	void update(float deltaTime);
	void cleanup();
};
