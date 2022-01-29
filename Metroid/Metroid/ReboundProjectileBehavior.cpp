#include "ReboundProjectileBehavior.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"

//Constructor
ReboundProjectileBehavior::ReboundProjectileBehavior() {}
//Destructor
ReboundProjectileBehavior::~ReboundProjectileBehavior() {}

//Basic update, gradually accelerate
void ReboundProjectileBehavior::Update() {
	physics->ApplyForce(force_x, force_y);
}
//Setup animation
void ReboundProjectileBehavior::InitAnim() {
	animator->SetAnimationSource(0, 36, 1, true);
}
void ReboundProjectileBehavior::BeginDeath() {
	animator->SetAnimationSource(78, 0, 2, false);
	ProjectileBehavior::BeginDeath();
}