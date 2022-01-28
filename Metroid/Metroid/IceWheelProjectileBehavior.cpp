#include "IceWheelProjectileBehavior.h"

IceWheelProjectileBehavior::IceWheelProjectileBehavior() {}
IceWheelProjectileBehavior::~IceWheelProjectileBehavior() {}

void IceWheelProjectileBehavior::Update() {
	physics->ApplyForce(force_x, force_y);
}

void IceWheelProjectileBehavior::InitAnim() {
	animator->SetAnimationSource(0, 0, 1, true);
}