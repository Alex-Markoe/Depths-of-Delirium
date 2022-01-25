//GUARD
#ifndef __COLLISIONCOMPONENT_H_INCLUDED__
#define __COLLISIONCOMPONENT_H_INCLUDED__

//FORWARD DEPENDENCIES
class GameObject;
class ObjectTreeNode;
class Handler;

//INCLUDE DEPENDENCIES
#include "Component.h"

//REPRESENTS THE TYPE OF OBJECT
//FOR COLLISION HANDLING LOGIC
enum OBJECT_TYPE {
	PLAYER,
	BOSS,
	PROJECTILE,
	OBSTACLE,
	ZONE
};

//HANDLE COLLISION
//AND OVERSEE THE MOVEMENT OF THE
//HITBOX, AS WELL AS FLAGGING MOVEMENT
//BETWEEN COLLISION QUADS
class CollisionComponent : public Component {
public:
	CollisionComponent(GameObject* _obj, SDL_Rect _position, SDL_Point hitboxOffset, OBJECT_TYPE _type);
	~CollisionComponent();
	void Update() override;
	void UpdatePosition(SDL_Rect position);
	void CollisionHandler(GameObject* other, float f_x, float f_y);
	void SetHandler(Handler* _handler);
	void ResetQuad();
	void SetQuad(int _index, ObjectTreeNode* _quad);
	void SetHitbox(SDL_Rect _hitbox);

	SDL_Rect hitbox;
	OBJECT_TYPE type;
	bool out_of_quad;
	int item_index;

private:
	GameObject* obj;
	Handler* handler;
	ObjectTreeNode* quad;
	SDL_Point HITBOX_OFFSET;
};

#endif //__COLLISIONCOMPONENT_H_INCLUDED__