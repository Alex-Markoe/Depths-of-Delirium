#include "CollisionComponent.h"
#include "ObjectTreeNode.h"
#include "CollisionHandlers.h"

//Constructor
//Initialize variables and hitbox
CollisionComponent::CollisionComponent(GameObject* _obj, SDL_Rect _position, SDL_Point hitboxOffset, OBJECT_TYPE _type) {
	HITBOX_OFFSET = hitboxOffset;
	hitbox = { _position.x + HITBOX_OFFSET.x, _position.y + HITBOX_OFFSET.y, _position.w - (HITBOX_OFFSET.x * 2), _position.h - HITBOX_OFFSET.y };
	obj = _obj;
	type = _type;
	out_of_quad = false;
	item_index = -1;
}
//Destructor
CollisionComponent::~CollisionComponent() {
	handler = nullptr;
	obj = nullptr;
	ResetQuad();
}

//Fire the collision handler
void CollisionComponent::CollisionHandler(GameObject* other, float f_x, float f_y) {
	if (handler != nullptr) handler->Execute(other, obj, f_x, f_y);
}
//Setup the collision handler
void CollisionComponent::SetHandler(Handler* _handler) {
	handler = _handler;
}

//Update the position of the hitbox,
//and check if the object has moved outside of its quadrant
void CollisionComponent::UpdatePosition(SDL_Rect position) {
	hitbox.x = position.x + HITBOX_OFFSET.x;
	hitbox.y = position.y + HITBOX_OFFSET.y;
	if (quad == nullptr) return;
	if (hitbox.x + hitbox.w < quad->dimensions.x || hitbox.x > quad->dimensions.x + quad->dimensions.w ||
		hitbox.y + hitbox.h < quad->dimensions.y || hitbox.y > quad->dimensions.y + quad->dimensions.h) {
		out_of_quad = true;
	}
}
//Set the quadrant for the object
void CollisionComponent::SetQuad(int _index, ObjectTreeNode* _quad) {
	item_index = _index;
	quad = _quad;
	out_of_quad = false;
}
//Reset the quadrant
void CollisionComponent::ResetQuad() {
	if (item_index != -1 && quad != nullptr) 
		quad->Erase(item_index);
	quad = nullptr;
}
void CollisionComponent::Update() {}