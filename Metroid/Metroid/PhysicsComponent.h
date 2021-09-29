//GUARD
#ifndef __PHYSICSCOMPONENT_H_INCLUDED__
#define __PHYSICSCOMPONENT_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "Component.h"

//HANDLES KINEMATIC BASED
//MOVEMENT AND FORCE APPLICATION
class PhysicsComponent : public Component {
public:
	PhysicsComponent(SDL_Point max_velocity, SDL_Point _decceleration);
	~PhysicsComponent();
	void Update() override;
	void ApplyForce(SDL_Point force);
	void UpdatePosition(SDL_Rect& position, float deltaTime);

	SDL_Point acceleration;
	SDL_Point velocity;

private:
	SDL_Point MAX_VELOCITY;
	SDL_Point decceleration;
};

#endif //__PHYSICSCOMPONENT_H_INCLUDED__