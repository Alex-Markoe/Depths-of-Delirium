//GUARD
#ifndef __ANIMATIONCOMPONENT_H_INCLUDED__
#define __ANIMATIONCOMPONENT_H_INCLUDED__

//FORWARD DEPENDENCIES
class RenderComponent;

//INCLUDE DEPENDENCIES
#include "Component.h"

//HANDLES UPDATING THE SOURCE RECT
//TO PLAY SPECIFIC ANIMATION
class AnimationComponent : public Component {
public:
	AnimationComponent(RenderComponent* _renderer);
	~AnimationComponent();
	void Update() override;
	void SetAnimationSource(int sourceX, int sourceY, int maxFrame, bool _loop);
	void SetFrame(int _frame);
	void SetFrameRate(int _frame_rate);

private:
	RenderComponent* renderer;

	bool loop;
	int frame;
	int frame_rate;
	int MAX_FRAME;
	int ANIM_SOURCE_X;
};

#endif //__ANIMATIONCOMPONENT_H_INCLUDED__