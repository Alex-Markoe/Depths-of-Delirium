#include "PlayerProjectileBehavior.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "ParticleSystemComponent.h"
#include "ParticleSystemParams.h"

//Constructor
PlayerProjectileBehavior::PlayerProjectileBehavior(){}
//Destructor
PlayerProjectileBehavior::~PlayerProjectileBehavior(){}

//Basic update, gradually accelerate
void PlayerProjectileBehavior::Update() {
	ProjectileBehavior::Update();
	physics->ApplyForce(force_x, force_y);
	GetAngle();
}
//Setup animation
void PlayerProjectileBehavior::InitAnim() {
	animator->SetAnimationSource(0, 0, 2, true);
}
void PlayerProjectileBehavior::BeginDeath() {
	particles->Modify(ParticleSystemParams(0, 0, 400, 400, 20, 0, 360, false, false, 1.0f, 200, 0.0f, { 0, 100 }, {0, 0}, FIRE_PARTICLE, STRAIGHT_ACCELERATING));
	animator->SetAnimationSource(108, 0, 2, false);
	ProjectileBehavior::BeginDeath();
}