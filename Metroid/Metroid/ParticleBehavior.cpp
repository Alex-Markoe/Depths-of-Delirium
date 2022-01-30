#include "ParticleBehavior.h"
#include "PhysicsComponent.h"

//Constructor
ParticleBehavior::ParticleBehavior() {
}
//Destructor
ParticleBehavior::~ParticleBehavior() {
	physics = nullptr;
}

//Setters
void ParticleBehavior::SetVelocity(SDL_Point _velocity) { velocity = _velocity; if (physics != nullptr) physics->ApplyForce(velocity.x, velocity.y); } //Apply velocity as well
void ParticleBehavior::SetPhysics(PhysicsComponent* _physics) { physics = _physics; }