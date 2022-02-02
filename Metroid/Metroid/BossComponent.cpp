#include "BossComponent.h"
#include "BossBehavior.h"

//Constructor
BossComponent::BossComponent(){}
//Destructor
BossComponent::~BossComponent() {
	if (behavior != nullptr) delete behavior;
}
//Replace the current behavior for the boss
void BossComponent::SetBehavior(BossBehavior* _behavior) {
	if (behavior != nullptr) delete behavior;
	behavior = _behavior;
}

void BossComponent::Update() {

}