#include "PhysicsComponent.h"

//Constructor
PhysicsComponent::PhysicsComponent(SDL_Point max_velocity, float _decell_x, float _decell_y) {
	velocity_x = 0;
	velocity_y = 0;
	acceleration_x = 0;
	acceleration_y = 0;
	MAX_VELOCITY = max_velocity;
	decell_x = _decell_x;
	decell_y = _decell_y;
}
//Destructor
PhysicsComponent::~PhysicsComponent() {}

//Apply a force to the object
void PhysicsComponent::ApplyForce(int f_x, int f_y) {
	acceleration_x += f_x;
	acceleration_y += f_y;
}
//Reset the object's kinematics
void PhysicsComponent::ResetKinematics(bool x, bool y) {
	if (x) {
		acceleration_x = 0;
		velocity_x = 0;
	}
	if (y) {
		acceleration_y = 0;
		velocity_y = 0;
	}
}

//Update the object's position based on any recently applied forces
void PhysicsComponent::UpdatePosition(SDL_Rect& position, float deltaTime) {
	velocity_x += acceleration_x * deltaTime;
	velocity_y += acceleration_y * deltaTime;

	if (abs(velocity_y) > MAX_VELOCITY.y)
		velocity_y = MAX_VELOCITY.y * (velocity_y / abs(velocity_y));
	if (abs(velocity_x) > MAX_VELOCITY.x)
		velocity_x = MAX_VELOCITY.x * (velocity_x / abs(velocity_x));
	
	position.x += velocity_x;
	position.y += velocity_y;

	acceleration_x = 0;
	acceleration_y = 0;
	velocity_x *= decell_x;
	velocity_y *= decell_y;
}

void PhysicsComponent::Update(){}