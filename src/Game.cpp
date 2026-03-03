#include "Game.h"
#include "GameObject.h"
#include "Renderer.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

Game::Game(int width, int height, Renderer& renderer)
    : screenWidth(width),
      screenHeight(height),
      renderer(renderer)
{}

void Game::init()
{
    GameObject player;

    player.x = 100.0f;
    player.y = 100.0f;
    player.width = 50.0f;
    player.height = 50.0f;

    player.velocityX = 0.0f;
    player.velocityY = 0.0f;
    player.speed = 300.0f;

    objects.push_back(player);

    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < 10; i++) {
	GameObject obj;

	obj.x = rand() % (screenWidth - 50);
	obj.y = rand() % (screenHeight - 50);

	obj.width = 50.0f;
	obj.height = 50.0f;

	obj.velocityX = 0.0f;
	obj.velocityY = 0.0f;
	obj.speed = 0.0f;

	objects.push_back(obj);
    }
}

static bool checkCollision(const GameObject& a, const GameObject& b){
    bool collisionX = a.x < b.x + a.width && a.x + a.width > b.x;

    bool collisionY = a.y < b.y + a.height && a.y + a.height > b.y;

    return collisionX && collisionY;
}

void Game::processInput(GLFWwindow* window)
{
    objects[0].velocityX = 0.0f;
    objects[0].velocityY = 0.0f;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        objects[0].velocityX = -objects[0].speed;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        objects[0].velocityX = objects[0].speed;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        objects[0].velocityY = objects[0].speed;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        objects[0].velocityY = -objects[0].speed;
}

void Game::update(float deltaTime)
{
    for(auto& obj : objects)
	obj.update(deltaTime);

    GameObject& player = objects[0];
    for (size_t i = 1; i < objects.size(); i++) {
	if(checkCollision(player, objects[i])) {
	    player.x -= player.velocityX * deltaTime;
	    player.y -= player.velocityY * deltaTime;
	}
    }

    for(auto& obj : objects) {
	obj.x = std::clamp(obj.x, 0.0f, (float)screenWidth - obj.width);

	obj.y = std::clamp(obj.y, 0.0f, (float)screenHeight - obj.height);
    }
}

void Game::render()
{
    for (const auto& obj : objects)
	renderer.draw(obj);
}

void Game::resize(int width, int height)
{
    screenWidth = width;
    screenHeight = height;

    renderer.resize(width, height);
}
