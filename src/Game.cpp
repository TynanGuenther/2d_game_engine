#include "Game.h"
#include "Renderer.h"
#include <algorithm>

Game::Game(int width, int height, Renderer& renderer)
    : screenWidth(width),
      screenHeight(height),
      renderer(renderer)
{}

void Game::init()
{
    player.x = 100.0f;
    player.y = 100.0f;
    player.width = 50.0f;
    player.height = 50.0f;

    player.velocityX = 0.0f;
    player.velocityY = 0.0f;

    player.speed = 300.0f;
}

void Game::processInput(GLFWwindow* window)
{
    player.velocityX = 0.0f;
    player.velocityY = 0.0f;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player.velocityX = -player.speed;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player.velocityX = player.speed;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player.velocityY = player.speed;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player.velocityY = -player.speed;
}

void Game::update(float deltaTime)
{
    player.update(deltaTime);

    player.x = std::clamp(player.x, 0.0f,
                          (float)screenWidth - player.width);

    player.y = std::clamp(player.y, 0.0f,
                          (float)screenHeight - player.height);
}

void Game::render()
{
    renderer.draw(player);
}

void Game::resize(int width, int height)
{
    screenWidth = width;
    screenHeight = height;

    renderer.resize(width, height);
}
