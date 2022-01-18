#include "ParticleComponent.h"
#include "PhysicsComponent.h"
#include "ParticleBehavior.h"

ParticleComponent::ParticleComponent(PhysicsComponent* _physics, ParticleBehavior* _behavior) {
	behavior = _behavior;
}
ParticleComponent::~ParticleComponent() {
	delete behavior;
}

void ParticleComponent::Update() {
	behavior->Update();
}
void ParticleComponent::SetVelocity(SDL_Point _velocity) {
	behavior->SetVelocity(_velocity);
}