#include "ReboundProjectileBehavior.h"

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