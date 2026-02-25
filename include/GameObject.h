#pragma once

struct GameObject {
    float x;
    float y;
    float width;
    float height;

    float velocityX;
    float velocityY;
    float speed;

    void update(float deltaTime);
};
