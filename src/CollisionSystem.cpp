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

    float overlapX1 = (ax + aw) - bx;
    float overlapX2 = (bx + bw) - ax;
    float overlapY1 = (ay + ah) - by;
    float overlapY2 = (by + bh) - ay;

    float overlapX = std::min(overlapX1, overlapX2);
    float overlapY = std::min(overlapY1, overlapY2);

    if (overlapX < overlapY)
    {
        if (overlapX1 < overlapX2)
            a.transform.position.x -= overlapX1;
        else
            a.transform.position.x += overlapX2;

        a.body.velocity.x = 0;
    }
    else
    {
        if (overlapY1 < overlapY2)
            a.transform.position.y -= overlapY1;
        else
            a.transform.position.y += overlapY2;

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
	    
