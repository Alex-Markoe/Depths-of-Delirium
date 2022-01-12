#include "AnimationComponent.h"
#include "RenderComponent.h"

//Constructor
AnimationComponent::AnimationComponent(RenderComponent* _renderer) {
	renderer = _renderer;
	frame = 0;
}
//Destructor
AnimationComponent::~AnimationComponent() {
	renderer = nullptr;
}

//Simple method that updates the animation frame
void AnimationComponent::Update() {
	frame++;
	if (frame / 7 > MAX_FRAME) { frame = 0; }
	renderer->sourceRect.x = ANIM_SOURCE_X + ((frame / 7) * renderer->sourceRect.w);
}

//Funtion to set the source rectangle in the case of changing states
void AnimationComponent::SetAnimationSource(int sourceX, int sourceY, int maxFrame) {
	ANIM_SOURCE_X = sourceX;
	MAX_FRAME = maxFrame;
	renderer->sourceRect.x = sourceX;
	renderer->sourceRect.y = sourceY;
}

void AnimationComponent::SetFrame(int _frame) { frame = _frame; }