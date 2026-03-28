#include "Game.h"
#include "GameObject.h"
#include "Renderer.h"
#include "CollisionSystem.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

CollisionSystem collisionSystem;

Game::Game(int width, int height, Renderer& renderer)
    : screenWidth(width),
      screenHeight(height),
      renderer(renderer)
{}

void Game::init()
{
    GameObject& player = scene.createObject();
    
    player.tag = Tag::Player;
    player.transform.position = {100.0f, 100.0f};
    player.transform.size = {50.0f, 50.0f};
    player.body.velocity = {0.0f, 0.0f};
    player.body.speed = 300.0f;
    player.isStatic = false;

    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < 10; i++) {
	GameObject obj = scene.createObject();

	obj.tag = Tag::Wall;
	obj.transform.position = {
	    (float)(rand() % (screenWidth - 50)),
	    (float)(rand() % (screenHeight - 50))
	};
    	
    	obj.transform.size = {50.0f, 50.0f};
    	obj.body.velocity = {0.0f, 0.0f};
    	obj.body.speed = 0.0f;
    	obj.isStatic = true;
    }
}

void Game::processInput(GLFWwindow* window)
{
    GameObject* player = scene.findByTag(Tag::Player);
    
    if(!player)
	return;

    player->body.velocity.x = 0.0f;
    player->body.velocity.y = 0.0f;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player->body.velocity.x = -scene.objects[0].body.speed;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player->body.velocity.x = scene.objects[0].body.speed;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player->body.velocity.y = scene.objects[0].body.speed;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player->body.velocity.y = -scene.objects[0].body.speed;
}

void Game::update(float deltaTime)
{
    scene.update(deltaTime);
    collisionSystem.checkCollisions(scene);
    for(auto& obj : scene.objects) {
	obj.transform.position.x = std::clamp(obj.transform.position.x, 0.0f, (float)screenWidth - obj.transform.size.x);

	obj.transform.position.y = std::clamp(obj.transform.position.y, 0.0f, (float)screenHeight - obj.transform.size.y);
    }
}

void Game::render()
{
    for (const auto& obj : scene.objects)
	renderer.draw(obj);
}

void Game::resize(int width, int height)
{
    screenWidth = width;
    screenHeight = height;

    renderer.resize(width, height);
}
