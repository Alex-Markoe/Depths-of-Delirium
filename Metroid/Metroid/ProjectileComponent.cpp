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
//Deactivate the projectile
//Update the behavior as well
void ProjectileComponent::Deactivate() { 
	if (!active) return;
	active = false;
	behavior->BeginDeath();
	death_timer = SDL_GetTicks();
	lifetime = 300; //All projectiles have same death time, for consistency
	timer = &ProjectileComponent::UpdateDeathTimer; //change function
}
//Getters/Setters
SDL_Point ProjectileComponent::GetForce() { return behavior->GetForce(); }
//Update for the active timer, deactivate upon completion
void ProjectileComponent::UpdateActiveTimer() {
	if (active_timer + lifetime < SDL_GetTicks()) {
		Deactivate();
	}
}
//Update for the death timer, die upon completion
void ProjectileComponent::UpdateDeathTimer() {
	if (death_timer + lifetime < SDL_GetTicks()) {
		dead = true;
	}
}