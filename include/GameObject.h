#pragma once

#include "Transform.h"
#include "RigidBody.h"

enum class Tag {
    None,
    Player,
    Wall,
    Enemy,
    Bullet,
    Food,
};

class GameObject {
    public:

	Transform transform;
	RigidBody body;

	bool isStatic = false;
	bool isAlive = true;

	Tag tag = Tag::None;

	void update(float deltaTime);
};

