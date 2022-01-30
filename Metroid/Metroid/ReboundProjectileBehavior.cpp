#include "ReboundProjectileBehavior.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"

//Constructor
ReboundProjectileBehavior::ReboundProjectileBehavior() {}
//Destructor
ReboundProjectileBehavior::~ReboundProjectileBehavior() {}

//Basic update, gradually accelerate
void ReboundProjectileBehavior::Update() {
	ProjectileBehavior::Update();
	physics->ApplyForce(force_x, force_y);
}
//Setup animation
void ReboundProjectileBehavior::InitAnim() {
	animator->SetAnimationSource(0, 36, 1, true);
}
//Start death, just do the animation and call base 
void ReboundProjectileBehavior::BeginDeath() {
	animator->SetAnimationSource(78, 36, 2, false);
	ProjectileBehavior::BeginDeath();
}