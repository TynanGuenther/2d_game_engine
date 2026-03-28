#include "Scene.h"
#include "GameObject.h"

GameObject& Scene::createObject() {
    objects.emplace_back();
    return objects.back();
}

void Scene::update(float deltaTime){
    for (auto& obj : objects) {
	obj.update(deltaTime);
    }

    cleanup();
}

void Scene::cleanup() {
    objects.erase(
	    std::remove_if(objects.begin(), objects.end(),
		[](const GameObject& obj) {
		    return !obj.isAlive;
		    }),
	    objects.end()
    );
}

GameObject* Scene::findByTag(Tag tag) {
    for (auto& obj : objects) {
	if (obj.tag == tag)
	    return &obj;
    }
    return nullptr;
}
