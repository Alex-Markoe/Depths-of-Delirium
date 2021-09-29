//GUARD
#ifndef __ANIMATIONCOMPONENT_H_INCLUDED__
#define __ANIMATIONCOMPONENT_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "Component.h"
#include "RenderComponent.h"

//HANDLES UPDATING THE SOURCE RECT
//TO PLAY SPECIFIC ANIMATION
class AnimationComponent : public Component {
public:
	AnimationComponent(RenderComponent* _renderer);
	~AnimationComponent();
	void Update() override;
	void SetAnimationSource(int sourceX, int sourceY, int maxFrame);
	void SetFrame(int _frame);

private:
	RenderComponent* renderer;

	int frame;
	int MAX_FRAME;
	int ANIM_SOURCE_X;
};

#endif //__ANIMATIONCOMPONENT_H_INCLUDED__