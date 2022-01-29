#include "ProjectileComponent.h"
#include "ProjectileBehavior.h"
#include <functional>

//Constructor
//Setup variables for the behavior, lazy initialization
ProjectileComponent::ProjectileComponent(int _lifeTime, PhysicsComponent* _physics, CollisionComponent* _collider, RenderComponent* _renderer, AnimationComponent* _animator, 
										 ParticleSystemComponent* _particles, ProjectileBehavior* _behavior) {
	active = true;
	dead = false;
	behavior = _behavior;
	active_timer = SDL_GetTicks();
	death_timer = 0;
	lifetime = _lifeTime;
	behavior->Init(_physics, _collider, _renderer, _animator, _particles);
	behavior->InitAnim();
	timer = &ProjectileComponent::UpdateActiveTimer;
}
//Destructor
ProjectileComponent::~ProjectileComponent(){
	delete behavior;
}
//Update projectile
//Check if the projectile is no longer active
void ProjectileComponent::Update(){
	(this->*timer)();
	behavior->Update();
}
void ProjectileComponent::SetForce(int f_x, int f_y) { behavior->SetForce(f_x, f_y); }
void ProjectileComponent::Deactivate() { 
	if (!active) return;
	active = false;
	behavior->BeginDeath();
	death_timer = SDL_GetTicks();
	lifetime = 300;
	timer = &ProjectileComponent::UpdateDeathTimer;
}
SDL_Point ProjectileComponent::GetForce() { return behavior->GetForce(); }
void ProjectileComponent::UpdateActiveTimer() {
	if (active_timer + lifetime < SDL_GetTicks()) {
		Deactivate();
	}
}
void ProjectileComponent::UpdateDeathTimer() {
	if (death_timer + lifetime < SDL_GetTicks()) {
		dead = true;
	}
}