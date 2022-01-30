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
	void ApplyForce(int f_x, int f_y);
	void UpdatePosition(SDL_Rect& position, float deltaTime);
	void ResetKinematics(bool x, bool y); //true for reset, false for no reset

	int acceleration_x;
	int acceleration_y;
	int velocity_x;
	int velocity_y;

private:
	SDL_Point MAX_VELOCITY;
	float decell_x;
	float decell_y;
};

#endif //__PHYSICSCOMPONENT_H_INCLUDED__