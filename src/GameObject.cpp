#include "GameObject.h"

void GameObject::update(float deltaTime) {
    x += velocityX * deltaTime;
    y += velocityY * deltaTime;
}

