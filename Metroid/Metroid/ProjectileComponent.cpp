#include "ProjectileComponent.h"
#include "ProjectileBehavior.h"

//Constructor
//Setup variables for the behavior, lazy initialization
ProjectileComponent::ProjectileComponent(int _lifeTime, PhysicsComponent* _physics, RenderComponent* _renderer, AnimationComponent* _animator, ProjectileBehavior* _behavior) {
	active = true;
	behavior = _behavior;
	activeTimer = SDL_GetTicks() + _lifeTime;
	behavior->physics = _physics;
	behavior->renderer = _renderer;
	behavior->animator = _animator;
	behavior->InitAnim();
}
//Destructor
ProjectileComponent::~ProjectileComponent(){
	delete behavior;
}
//Update projectile
//Check if the projectile is no longer active
void ProjectileComponent::Update(){
	if (activeTimer < SDL_GetTicks()) active = false;
	behavior->Update();
}