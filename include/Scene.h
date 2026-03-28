#pragma once
#include <vector>
#include <algorithm>
#include "GameObject.h"

class Scene {
    public:
	std::vector<GameObject> objects;
	
	GameObject& createObject();
	GameObject* findByTag(Tag tag);
	void update(float deltaTime);
	void cleanup();
};
