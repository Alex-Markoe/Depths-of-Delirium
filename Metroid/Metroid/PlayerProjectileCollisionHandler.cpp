#include "PlayerProjectileCollisionHandler.h"
#include "ProjectileComponent.h"
#include "GameObject.h"

void PlayerProjectileCollisionHandler::ObstacleCollision(GameObject* other, GameObject* obj, int f_x, int f_y) {
	ProjectileComponent* p = (ProjectileComponent*)obj->components[0];
	p->Deactivate();
}