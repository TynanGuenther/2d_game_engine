#include "Game.h"
#include "GameObject.h"
#include "Renderer.h"
#include "CollisionSystem.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

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
    player.body.speed = 300.0f;
    player.isStatic = false;

    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < 10; i++) {
	GameObject& obj = scene.createObject();
	obj.tag = Tag::Wall;
	obj.transform.position = {
	    (float)(rand() % (screenWidth - 50)),
	    (float)(rand() % (screenHeight - 50))
	};
    	
    	obj.transform.size = {50.0f, 50.0f};
    	obj.isStatic = true;
	obj.isAlive = true;
    }
        // Borders
    GameObject& leftWall = scene.createObject();
    leftWall.tag = Tag::Wall;
    leftWall.transform.position = {0, 0};
    leftWall.transform.size = {0, (float)screenHeight};
    leftWall.isStatic = true;

    GameObject& rightWall = scene.createObject();
    rightWall.tag = Tag::Wall;
    rightWall.transform.position = {(float)screenWidth, 0};
    rightWall.transform.size = {0, (float)screenHeight};
    rightWall.isStatic = true;

    GameObject& topWall = scene.createObject();
    topWall.tag = Tag::Wall;
    topWall.transform.position = {0, (float)screenHeight};
    topWall.transform.size = {(float)screenWidth, 0};
    topWall.isStatic = true;

    GameObject& bottomWall = scene.createObject();
    bottomWall.tag = Tag::Wall;
    bottomWall.transform.position = {0, 0};
    bottomWall.transform.size = {(float)screenWidth, 0};
    bottomWall.isStatic = true;

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
}

void Game::render()
{
    for (const auto& obj : scene.objects)
    {
	renderer.draw(obj);
    }
}

void Game::resize(int width, int height)
{
    screenWidth = width;
    screenHeight = height;

    renderer.resize(width, height);
}
