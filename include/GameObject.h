#pragma once

#include "Transform.h"
#include "RigidBody.h"

class GameObject {
    public:

	Transform transform;
	RigidBody body;

	bool isStatic = false;

	void update(float deltaTime);
};

