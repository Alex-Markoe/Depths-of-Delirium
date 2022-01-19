//GUARD
#ifndef __PARTICLEBEHAVIOR_H_INCLUDED__
#define __PARTICLEBEHAVIOR_H_INCLUDED__

//FORWARD DEPENDENCIES
class PhysicsComponent;

//INCLUDE DEPENDENCIES
#include <SDL.h>

//PARTICLE BEHAVIOR
//BASE CLASS THAT DEFINES THE WAY THAT PARTICLES MOVE
//Has virtual update and reset methods for different behaviors
class ParticleBehavior{
public:
	ParticleBehavior();
	~ParticleBehavior();
	virtual void Update(){};
	virtual void Reset(){};
	void SetVelocity(SDL_Point _velocity);
	void SetPhysics(PhysicsComponent* _physics);

protected:
	PhysicsComponent* physics;
	SDL_Point velocity;
};

#endif //__PARTICLEBEHAVIOR_H_INCLUDED__