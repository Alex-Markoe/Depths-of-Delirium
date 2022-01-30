#include "ProjectileBehavior.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "ParticleSystemComponent.h"

//Constructor
ProjectileBehavior::ProjectileBehavior() {
	Init(nullptr, nullptr, nullptr, nullptr, nullptr);
	dead = false;
}
//Destructor
ProjectileBehavior::~ProjectileBehavior() {
	Init(nullptr, nullptr, nullptr, nullptr, nullptr);
}
//Initialize,
//setup component references
void ProjectileBehavior::Init(PhysicsComponent* _physics, CollisionComponent* _collider, RenderComponent* _renderer, AnimationComponent* _animator, ParticleSystemComponent* _particles) {
	physics = _physics;
	renderer = _renderer;
	animator = _animator;
	particles = _particles;
	collider = _collider;
}
//Update, get out if already dead
void ProjectileBehavior::Update() {
	if (dead) return;
}
//Set the projectile's current force application
void ProjectileBehavior::SetForce(int f_x, int f_y) {
	force_x = f_x; 
	force_y = f_y;
}
//Get the force of the projectile
SDL_Point ProjectileBehavior::GetForce() {
	return { force_x, force_y };
}
//Get the angle at which the projectile should be pointing, if necessary
void ProjectileBehavior::GetAngle() {
	float angle = atan2(physics->velocity_y, physics->velocity_x);
	renderer->SetAngle(angle * 180 / M_PI);
}
//Start the death logic for this projectile
//Mainly, change its animation, and 
//set it so that it no longer moves
//Also reset particles if needed
void ProjectileBehavior::BeginDeath() {
	physics->ResetKinematics(true, true);
	SetForce(0, 0);
	renderer->SetAngle(0);
	collider->SetInactive();
	if (particles != nullptr) particles->Reset();
	dead = true;
}
