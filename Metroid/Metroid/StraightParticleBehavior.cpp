#include "StraightParticleBehavior.h"
#include "PhysicsComponent.h"

StraightParticleBehavior::StraightParticleBehavior(){}
StraightParticleBehavior::~StraightParticleBehavior(){}

void StraightParticleBehavior::Update() {
	physics->ApplyForce(velocity.x, velocity.y);
}