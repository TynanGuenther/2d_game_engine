#include "GameObject.h"

void GameObject::update(float deltaTime) {
    if (isStatic) return;
    transform.position.x += body.velocity.x * deltaTime;
    transform.position.y += body.velocity.y * deltaTime;
}

