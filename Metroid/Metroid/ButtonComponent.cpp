#include "ButtonComponent.h"

//Constructor
ButtonComponent::ButtonComponent(CollisionComponent* _collider, ButtonCommand* _onclick_cmd) {
	mouse_pos = SDL_Point{ 0, 0 };
	collider = _collider;
	onclick_cmd = _onclick_cmd;
}
//Destructor
ButtonComponent::~ButtonComponent() {
	collider = nullptr;
	onclick_cmd = nullptr;
}

void ButtonComponent::Update() {
	SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
	if (Hover(mouse_pos, collider->hitbox) && SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1)) {
		onclick_cmd->Execute();
	}
}

//HELPER METHODS
bool Hover(SDL_Point mouse_pos, SDL_Rect hitbox) {
	return mouse_pos.x >= hitbox.x && mouse_pos.x <= hitbox.x + hitbox.w &&
		mouse_pos.y >= hitbox.y && mouse_pos.y <= hitbox.y + hitbox.h;
}