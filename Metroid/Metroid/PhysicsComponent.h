//GUARD
#ifndef __PHYSICSCOMPONENT_H_INCLUDED__
#define __PHYSICSCOMPONENT_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "Component.h"

//HANDLES KINEMATIC BASED
//MOVEMENT AND FORCE APPLICATION
class PhysicsComponent : public Component {
public:
	PhysicsComponent(SDL_Point max_velocity, float _decell_x, float _decell_y);
	~PhysicsComponent();
	void Update() override;
	void ApplyForce(SDL_Point force);
	void UpdatePosition(SDL_Rect& position, float deltaTime);
	void ResetKinematics();

	float acceleration_x;
	float acceleration_y;
	float velocity_x;
	float velocity_y;

private:
	SDL_Point MAX_VELOCITY;
	float decell_x;
	float decell_y;
};

#endif //__PHYSICSCOMPONENT_H_INCLUDED__