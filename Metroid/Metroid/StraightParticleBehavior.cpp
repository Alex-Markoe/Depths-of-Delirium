#include "StraightParticleBehavior.h"
#include "PhysicsComponent.h"

//constructor
StraightParticleBehavior::StraightParticleBehavior(){}
//destructor
StraightParticleBehavior::~StraightParticleBehavior(){}

//Apply the velocity
void StraightParticleBehavior::Update() {
	physics->ApplyForce(velocity.x, velocity.y);
}