#include "ProjectileBehavior.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"
#include "ParticleSystemComponent.h"

ProjectileBehavior::ProjectileBehavior() {
	Init(nullptr, nullptr, nullptr, nullptr, nullptr);
	dead = false;
}
ProjectileBehavior::~ProjectileBehavior() {
	Init(nullptr, nullptr, nullptr, nullptr, nullptr);
}
void ProjectileBehavior::Init(PhysicsComponent* _physics, CollisionComponent* _collider, RenderComponent* _renderer, AnimationComponent* _animator, ParticleSystemComponent* _particles) {
	physics = _physics;
	renderer = _renderer;
	animator = _animator;
	particles = _particles;
	collider = _collider;
}

void ProjectileBehavior::Update() {
	if (dead) return;
}
void ProjectileBehavior::SetForce(int f_x, int f_y) {
	force_x = f_x; 
	force_y = f_y;
}
SDL_Point ProjectileBehavior::GetForce() {
	return { force_x, force_y };
}
void ProjectileBehavior::GetAngle() {
	float angle = atan2(physics->velocity_y, physics->velocity_x);
	renderer->SetAngle(angle * 180 / M_PI);
}
void ProjectileBehavior::BeginDeath() {
	physics->ResetKinematics(true, true);
	SetForce(0, 0);
	renderer->SetAngle(0);
	collider->SetInactive();
	if (particles != nullptr) particles->Reset();
	dead = true;
}
