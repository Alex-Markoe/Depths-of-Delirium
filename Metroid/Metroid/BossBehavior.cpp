#include "BossBehavior.h"

//Constructor
BossBehavior::BossBehavior() {
}
//Destructor
BossBehavior::~BossBehavior() {
	anim = nullptr;
	physics = nullptr;
	collider = nullptr;
}
//Initialize references
void BossBehavior::Init(AnimationComponent* _anim, PhysicsComponent* _physics, CollisionComponent* _collider) {
	anim = _anim;
	physics = _physics;
	collider = _collider;
}
void BossBehavior::Update(){}