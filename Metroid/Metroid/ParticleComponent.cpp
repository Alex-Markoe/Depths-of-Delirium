#include "ParticleComponent.h"
#include "PhysicsComponent.h"
#include "ParticleBehavior.h"

//Constructor
ParticleComponent::ParticleComponent(PhysicsComponent* _physics, ParticleBehavior* _behavior) {
	behavior = _behavior;
}
//Destructor
ParticleComponent::~ParticleComponent() {
	delete behavior;
}

//Update behavior
void ParticleComponent::Update() {
	behavior->Update();
}
//Set velocity of behavior
void ParticleComponent::SetVelocity(SDL_Point _velocity) {
	behavior->Reset();
	behavior->SetVelocity(_velocity);
}