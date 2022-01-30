#include "IceWheelCollisionHandler.h"
#include "GameObject.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "ProjectileComponent.h"

//CHANGE DIRECTION TO RIGHT PERPENDICULAR 
//WHEN COLLIDING WITH OBSTACLE
void IceWheelCollisionHandler::ObstacleCollision(GameObject* other, GameObject* obj, int f_x, int f_y) {
	if (abs(f_x) < abs(f_y)) {
		obj->position.x -= f_x;
		obj->physics->ResetKinematics(true, false);
	}
	else {
		obj->position.y -= f_y;
		obj->physics->ResetKinematics(false, true);
	}
	obj->collider->UpdatePosition(obj->position);
	ProjectileComponent* p = (ProjectileComponent*)obj->components[0];
	SDL_Point force = p->GetForce();
	p->SetForce(force.y, -force.x);
}