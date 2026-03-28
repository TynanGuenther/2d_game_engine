#pragma once
#include "Scene.h"

class CollisionSystem 
{
    public:
	void checkCollisions(Scene& scene);

    private:
	bool AABB(const GameObject& a, const GameObject& b);
	void resolveCollision(GameObject& a, GameObject& b);
};
