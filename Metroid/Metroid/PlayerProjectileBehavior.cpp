#include "PlayerProjectileBehavior.h"

//Constructor
PlayerProjectileBehavior::PlayerProjectileBehavior(){}
//Destructor
PlayerProjectileBehavior::~PlayerProjectileBehavior(){}

//Basic update, gradually accelerate
void PlayerProjectileBehavior::Update() {
	physics->ApplyForce(force_x, force_y);
	GetAngle();
}
//Setup animation
void PlayerProjectileBehavior::InitAnim() {
	animator->SetAnimationSource(0, 21, 1, true);
}