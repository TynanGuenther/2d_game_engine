#include "Scene.h"

void Scene::update(float deltaTime){
    for (auto& obj : objects) {
	obj.update(deltaTime);
    }
}
