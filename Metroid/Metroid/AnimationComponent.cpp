#include "AnimationComponent.h"
#include "RenderComponent.h"

//Constructor
AnimationComponent::AnimationComponent(RenderComponent* _renderer) {
	renderer = _renderer;
	frame = 0;
	frame_rate = 7;
	loop = true;
}
//Destructor
AnimationComponent::~AnimationComponent() {
	renderer = nullptr;
}

//Simple method that updates the animation frame
void AnimationComponent::Update() {
	frame++;
	if (frame / frame_rate > MAX_FRAME) {
		if (loop) frame = 0;
		else frame--;
	}
	renderer->sourceRect.x = ANIM_SOURCE_X + ((frame / frame_rate) * renderer->sourceRect.w);
}

//Funtion to set the source rectangle in the case of changing states
void AnimationComponent::SetAnimationSource(int sourceX, int sourceY, int maxFrame, bool _loop) {
	ANIM_SOURCE_X = sourceX;
	MAX_FRAME = maxFrame;
	renderer->sourceRect.x = sourceX;
	renderer->sourceRect.y = sourceY;
	loop = _loop;
}

//Setters
void AnimationComponent::SetFrame(int _frame) { frame = _frame; }
void AnimationComponent::SetFrameRate(int _frame_rate) { frame_rate = _frame_rate; }