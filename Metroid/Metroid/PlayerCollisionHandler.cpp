#include "PlayerCollisionHandler.h"
#include "GameObject.h"
#include "PhysicsComponent.h"

void PlayerCollisionHandler::ObstacleCollision(GameObject* obj, int f_x, int f_y) {
	obj->physics->ApplyForce(f_x, f_y);
}
