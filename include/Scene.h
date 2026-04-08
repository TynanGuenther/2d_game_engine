#pragma once
#include <vector>
#include "GameObject.h"

class Scene {
    public:
	Scene();
	std::vector<GameObject> objects;
	
	GameObject& createObject();
	GameObject* findByTag(Tag tag);
	void update(float deltaTime);
	void cleanup();
};
