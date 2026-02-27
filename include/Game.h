#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GameObject.h"

class Renderer;

class Game {
public:
    Game(int width, int height, Renderer& renderer);

    void init();
    void processInput(GLFWwindow* window);
    void update(float deltaTime);
    void render();
    void resize(int width, int height);

private:
    int screenWidth;
    int screenHeight;

    Renderer& renderer;

    GameObject player;
};
