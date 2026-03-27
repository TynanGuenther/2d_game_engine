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


    player.transform.position = {100.0f, 100.0f};
    player.transform.size = {50.0f, 50.0f};
    
    player.body.velocity = {0.0f, 0.0f};
    player.body.speed = 300.0f;
    
    player.isStatic = false;
    
    scene.objects.push_back(player);

    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 0; i < 10; i++) {
	GameObject obj;


	obj.transform.position = {
	    (float)(rand() % (screenWidth - 50)),
	    (float)(rand() % (screenHeight - 50))
	};
    	
    	obj.transform.size = {50.0f, 50.0f};
    	
    	obj.body.velocity = {0.0f, 0.0f};
    	obj.body.speed = 0.0f;
    	
    	obj.isStatic = true;

	scene.objects.push_back(obj);
    }
}

static bool checkCollision(const GameObject& a, const GameObject& b){
    bool collisionX = a.transform.position.x < b.transform.position.x + a.transform.size.x && a.transform.position.x + a.transform.size.x > b.transform.position.x;

    bool collisionY = a.transform.position.y < b.transform.position.y + a.transform.size.y && a.transform.position.y + a.transform.size.y > b.transform.position.y;

    return collisionX && collisionY;
}

void Game::processInput(GLFWwindow* window)
{
    scene.objects[0].body.velocity.x = 0.0f;
    scene.objects[0].body.velocity.y = 0.0f;

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        scene.objects[0].body.velocity.x = -scene.objects[0].body.speed;

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        scene.objects[0].body.velocity.x = scene.objects[0].body.speed;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        scene.objects[0].body.velocity.y = scene.objects[0].body.speed;

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        scene.objects[0].body.velocity.y = -scene.objects[0].body.speed;
}

void Game::update(float deltaTime)
{
    for(auto& obj : scene.objects)
	obj.update(deltaTime);

    GameObject& player = scene.objects[0];

    player.transform.position.x += player.body.velocity.x * deltaTime;

    for (size_t i = 1; i < scene.objects.size(); i++) {
	if(checkCollision(player, scene.objects[i])) {
	    if(player.body.velocity.x > 0)//right
		player.transform.position.x = scene.objects[i].transform.position.x - player.transform.size.x;
	    else if (player.body.velocity.x < 0)//left
		player.transform.position.x = scene.objects[i].transform.position.x + scene.objects[i].transform.size.x;
	}
    }
    player.transform.position.y += player.body.velocity.y * deltaTime;

    for (size_t i = 1; i < scene.objects.size(); i++) {
	if(checkCollision(player, scene.objects[i])) {
	    if(player.body.velocity.y > 0)//up
		player.transform.position.y = scene.objects[i].transform.position.y - player.transform.size.y;
	    else if (player.body.velocity.y < 0)//down
		player.transform.position.y = scene.objects[i].transform.position.y + scene.objects[i].transform.size.y;
	}
    }

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
