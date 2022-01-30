#include "PlayerCollisionHandler.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "PlayerComponent.h"

//Helper function
//Return the force required to resolve
//a collision
//int GetForce(float deltaTime, int depth, int accel, int vel) {
//	int speed = (accel + vel) / deltaTime;
//	return (depth / deltaTime) + speed;
//}

//ADJUST POSITION WHEN COLLIDING WITH OBSTACLE
void PlayerCollisionHandler::ObstacleCollision(GameObject* other, GameObject* obj, int f_x, int f_y) {
	if (abs(f_x) < abs(f_y)) {
		obj->position.x -= f_x;
		obj->physics->ResetKinematics(true, false);
	}
	else {
		obj->position.y -= f_y;
		obj->physics->ResetKinematics(false, true);
		if (f_y >= 0) {
			PlayerComponent* p = (PlayerComponent*)obj->components[0];
			p->OnGround();
		}
	}
	obj->collider->UpdatePosition(obj->position);
	//obj->physics->ApplyForce(f_x, f_y);
}
