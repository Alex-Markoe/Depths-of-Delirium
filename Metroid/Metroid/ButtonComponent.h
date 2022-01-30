//GUARD
#ifndef __BUTTONCOMPONENT_H_INCLUDED__
#define __BUTTONCOMPONENT_H_INCLUDED__

//FORWARD DEPENDENCIES
class CollisionComponent;
class ButtonCommand;
class ButtonComponent;

//INCLUDE DEPENDENCIES
#include "Component.h"

//HELPER METHOD
bool Hover(SDL_Point mouse_pos, SDL_Rect hitbox);

//BUTTON COMPONENT
//DOES SOMETHING WHEN CLICKED
class ButtonComponent : public Component {
public:
	ButtonComponent(CollisionComponent* _collider, ButtonCommand* _onclick_cmd);
	~ButtonComponent();
	void Update() override;
	
private:
	SDL_Point mouse_pos;
	CollisionComponent* collider;
	ButtonCommand* onclick_cmd;
};

#endif //__BUTTONCOMPONENT_H_INCLUDED__