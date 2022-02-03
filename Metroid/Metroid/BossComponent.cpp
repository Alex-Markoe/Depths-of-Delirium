#include "BossComponent.h"
#include "BossBehavior.h"

//Constructor
BossComponent::BossComponent(){}
//Destructor
BossComponent::~BossComponent() {}
//Replace the current behavior for the boss
void BossComponent::SetBehavior(BossBehavior* _behavior) {
	behavior = _behavior;
}

void BossComponent::Update() {

}