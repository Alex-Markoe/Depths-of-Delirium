//GUARD
#ifndef __PROJECTILEBEHAVIOR_H_INCLUDED__
#define __PROJECTILEBEHAVIOR_H_INCLUDED__

//FORWARD DEPENDENCIES

//INCLUDE DEPENDENCIES
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "RenderComponent.h"
#include "ParticleSystemComponent.h"

//PROJECTILE BEHAVIOR
//HANDLES BEHAVIOR OF INDIVIDUAL 
//PROJECTILES
class ProjectileBehavior{
public:
	ProjectileBehavior(){};
	~ProjectileBehavior() { physics = nullptr; renderer = nullptr; animator = nullptr; particles = nullptr; };
	virtual void Update(){};
	virtual void InitAnim(){};
	void SetForce(int f_x, int f_y) { force_x = f_x; force_y = f_y; } //set intial force
	SDL_Point GetForce() { return { force_x, force_y }; }

	//Manage components
	PhysicsComponent* physics;
	RenderComponent* renderer;
	AnimationComponent* animator;
	ParticleSystemComponent* particles;

protected:
	void GetAngle() { //Visually update projectile to match trajectory
		float angle = atan2(physics->velocity_y, physics->velocity_x);
		renderer->SetAngle(angle * 180 / M_PI);
	};
	int force_x;
	int force_y;
};

#endif //__PROJECTILEBEHAVIOR_H_INCLUDED__