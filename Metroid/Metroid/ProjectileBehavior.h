//GUARD
#ifndef __PROJECTILEBEHAVIOR_H_INCLUDED__
#define __PROJECTILEBEHAVIOR_H_INCLUDED__

//FORWARD DEPENDENCIES
class PhysicsComponent;
class RenderComponent;
class AnimationComponent;
class ParticleSystemComponent;
class CollisionComponent;

//INCLUDE DEPENDENCIES
#include <SDL.h>

//PROJECTILE BEHAVIOR
//HANDLES BEHAVIOR OF INDIVIDUAL 
//PROJECTILES
class ProjectileBehavior{
public:
	ProjectileBehavior();
	~ProjectileBehavior();
	virtual void Update();
	virtual void InitAnim(){};
	void Init(PhysicsComponent* _physics, CollisionComponent* _collider, RenderComponent* _renderer, AnimationComponent* _animator, ParticleSystemComponent* _particles);
	void SetForce(int f_x, int f_y); //set intial force
	SDL_Point GetForce();
	virtual void BeginDeath();

	//Manage components
	PhysicsComponent* physics;
	RenderComponent* renderer;
	AnimationComponent* animator;
	ParticleSystemComponent* particles;
	CollisionComponent* collider;

protected:
	void GetAngle();

	int force_x;
	int force_y;
	bool dead;
};

#endif //__PROJECTILEBEHAVIOR_H_INCLUDED__