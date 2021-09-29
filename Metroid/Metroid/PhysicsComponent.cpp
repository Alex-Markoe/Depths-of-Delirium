#include "PhysicsComponent.h"
//Constructor
PhysicsComponent::PhysicsComponent(SDL_Point max_velocity, SDL_Point _decceleration) {
	velocity.x = 0;
	velocity.y = 0;
	MAX_VELOCITY = max_velocity;
	decceleration = _decceleration;
}
//Destructor
PhysicsComponent::~PhysicsComponent() {}

//Apply a force to the object
void PhysicsComponent::ApplyForce(SDL_Point force) {
	acceleration.x += force.x;
	acceleration.y += force.y;
}

//Update the object's position based on any recently applied forces
void PhysicsComponent::UpdatePosition(SDL_Rect& position, float deltaTime) {
	velocity.x += acceleration.x * deltaTime;
	velocity.y += acceleration.y * deltaTime;

	if (abs(velocity.y) > MAX_VELOCITY.y)
		velocity.y = MAX_VELOCITY.y * (velocity.y / abs(velocity.y));
	if (abs(velocity.x) > MAX_VELOCITY.x)
		velocity.x = MAX_VELOCITY.x * (velocity.x / abs(velocity.x));

	position.x += velocity.x;
	position.y += velocity.y;

	acceleration.x = 0;
	acceleration.y = 0;
	velocity.x *= decceleration.x;
	velocity.y *= decceleration.y;
}

void PhysicsComponent::Update(){}