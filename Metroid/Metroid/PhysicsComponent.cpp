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
void PhysicsComponent::ApplyForce(SDL_Point force) {
	acceleration_x += force.x;
	acceleration_y += force.y;
}

void PhysicsComponent::ResetKinematics() {
	acceleration_x = 0.0f;
	acceleration_y = 0.0f;
	velocity_x = 0.0f;
	velocity_y = 0.0f;
}

//Update the object's position based on any recently applied forces
void PhysicsComponent::UpdatePosition(SDL_Rect& position, float deltaTime) {
	velocity_x += acceleration_x;
	velocity_y += acceleration_y;

	if (fabs(velocity_y) > MAX_VELOCITY.y)
		velocity_y = MAX_VELOCITY.y * (velocity_y / fabs(velocity_y));
	if (fabs(velocity_x) > MAX_VELOCITY.x)
		velocity_x = MAX_VELOCITY.x * (velocity_x / fabs(velocity_x));
	
	position.x += velocity_x * deltaTime;
	position.y += velocity_y * deltaTime;

	acceleration_x = 0;
	acceleration_y = 0;
	velocity_x *= decell_x;
	velocity_y *= decell_y;
}

void PhysicsComponent::Update(){}