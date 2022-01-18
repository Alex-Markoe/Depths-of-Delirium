#include "ParticleBehavior.h"
#include "PhysicsComponent.h"

ParticleBehavior::ParticleBehavior() {
}
ParticleBehavior::~ParticleBehavior() {
	physics = nullptr;
}

void ParticleBehavior::SetVelocity(SDL_Point _velocity) { velocity = _velocity; if (physics != nullptr) physics->ApplyForce(velocity.x, velocity.y); }
void ParticleBehavior::SetPhysics(PhysicsComponent* _physics) { physics = _physics; }