//GUARD
#ifndef __PROJECTILEBEHAVIOR_H_INCLUDED__
#define __PROJECTILEBEHAVIOR_H_INCLUDED__

//FORWARD DEPENDENCIES

//INCLUDE DEPENDENCIES
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "RenderComponent.h"

//PROJECTILE BEHAVIOR
//HANDLES BEHAVIOR OF INDIVIDUAL 
//PROJECTILES
class ProjectileBehavior{
public:
	ProjectileBehavior(){};
	~ProjectileBehavior(){ physics = nullptr; renderer = nullptr; };
	virtual void Update(){};
	virtual void InitAnim(){};
	void SetForce(int f_x, int f_y) { force_x = f_x; force_y = f_y; } //set intial force

	//Manage components
	PhysicsComponent* physics;
	RenderComponent* renderer;
	AnimationComponent* animator;

protected:
	void GetAngle() { //Visually update projectile to match trajectory
		float angle = atan2(physics->velocity_y, physics->velocity_x);
		renderer->SetAngle(angle);
	};
	int force_x;
	int force_y;
};

#endif //__PROJECTILEBEHAVIOR_H_INCLUDED__