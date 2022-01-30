//GUARD
#ifndef __PROJECTILECOMPONENT_H_INCLUDED__
#define __PROJECTILECOMPONENT_H_INCLUDED__

//FORWARD DEPENDENCIES
class ProjectileBehavior;
class PhysicsComponent;
class RenderComponent;
class AnimationComponent;
class CollisionComponent;
class ParticleSystemComponent;

//INCLUDE DEPENDENCIES
#include "Component.h"

//MODIFIABLE PROJECTILE BEHAVIOR
//HOOK UP BEHAVIOR FOR SPECIALIZED STUFF
class ProjectileComponent : public Component {
public:
	ProjectileComponent(int _lifeTime, PhysicsComponent* _physics, CollisionComponent* _collider, RenderComponent* _renderer, 
						AnimationComponent* _animator, ParticleSystemComponent* _particles, ProjectileBehavior* _behavior);
	~ProjectileComponent();
	void Update() override;
	void Deactivate();
	void SetForce(int f_x, int f_y);
	SDL_Point GetForce();

	bool active; //IF PROJETILE IS STILL MOVING
	bool dead; //PROJECTILE NEEDS TO BE DESTROYED

private:
	void UpdateActiveTimer();
	void UpdateDeathTimer();

	Uint32 active_timer;
	Uint32 death_timer;
	int lifetime;
	ProjectileBehavior* behavior;
	void (ProjectileComponent::*timer)(); //FUNCTION POINTER FOR TIMER BEHAVIOR
};

#endif //__PROJECTILECOMPONENT_H_INCLUDED__