#include "ReboundCollisionHandler.h"
#include "ProjectileComponent.h"
#include "PhysicsComponent.h"
#include "PlayerComponent.h"
#include "GameObject.h"

ReboundCollisionHandler::~ReboundCollisionHandler() {
	player = nullptr;
}

void ReboundCollisionHandler::ObstacleCollision(GameObject* other, GameObject* obj, int f_x, int f_y) {
	ApplyBounce(obj);
}
void ReboundCollisionHandler::SetPlayer(GameObject* _player) {
	player = _player;
}
void ReboundCollisionHandler::ApplyBounce(GameObject* obj) {
	ProjectileComponent* p = (ProjectileComponent*)obj->components[0];
	if (player != nullptr) {
		player->physics->ResetKinematics(true, true);
		player->physics->ApplyForce(-obj->physics->velocity_x * 40, -obj->physics->velocity_y * 40);
		PlayerComponent* p_c = (PlayerComponent*)player->components[0];
		p_c->ResetJump();
	}
	p->Deactivate();
}