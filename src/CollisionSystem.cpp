#include "CollisionSystem.h"
#include "GameObject.h"


bool CollisionSystem::AABB(const GameObject& a, const GameObject& b) {
    return (
	    a.transform.position.x < b.transform.position.x + b.transform.size.x &&
	    a.transform.position.x + a.transform.size.x > b.transform.position.x &&
	    a.transform.position.y < b.transform.position.y + b.transform.size.y &&
	    a.transform.position.y + a.transform.size.y > b.transform.position.y 
    );
} 

void CollisionSystem::resolveCollision(GameObject& a, GameObject& b) {
    if (a.isStatic) return;

    float ax = a.transform.position.x;
    float ay = a.transform.position.y;
    float aw = a.transform.size.x;
    float ah = a.transform.size.y;
    
    float bx = b.transform.position.x;
    float by = b.transform.position.y;
    float bw = b.transform.size.x;
    float bh = b.transform.size.y;

    float overlapX = (ax + aw / 2) - (bx + bw / 2);
    float overlapY = (ay + ah / 2) - (by + bh / 2);

    if (std::abs(overlapX) > std::abs(overlapY)) {
	if (overlapX > 0)
	    a.transform.position.x = bx + bw;
	else
	    a.transform.position.x = bx - aw;
	a.body.velocity.x = 0;
    } else {
	if (overlapY > 0) 
	    a.transform.position.y = by + bh;
	else
	    a.transform.position.y = by - ah;
	a.body.velocity.y = 0;
    }
}

void CollisionSystem::checkCollisions(Scene& scene) {
    auto& objects = scene.objects;

    for (size_t i = 0; i < objects.size(); i++) {
	for(size_t j = i + 1; j < objects.size(); j++) {
	    GameObject& a = objects[i];
	    GameObject& b = objects[j];
	    if (AABB(a,b)) {
		if (a.tag == Tag::Player && b.tag == Tag::Wall)
		    resolveCollision(a, b);
		if (b.tag == Tag::Player && a.tag == Tag::Wall)
		    resolveCollision(b, a);
		}
	}
    }

}
	    
