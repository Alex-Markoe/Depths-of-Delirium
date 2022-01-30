#include "IceWheelProjectileBehavior.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"

//Constructor
IceWheelProjectileBehavior::IceWheelProjectileBehavior() {}
//Destructor
IceWheelProjectileBehavior::~IceWheelProjectileBehavior() {}

//Update, gradually accelerate
void IceWheelProjectileBehavior::Update() {
	physics->ApplyForce(force_x, force_y);
}
//Setup animation
void IceWheelProjectileBehavior::InitAnim() {
	animator->SetAnimationSource(0, 0, 1, true);
}