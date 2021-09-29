#pragma once
//GUARD
#ifndef __COLLISIONCOMPONENT_H_INCLUDED__
#define __COLLISIONCOMPONENT_H_INCLUDED__

//FORWARD DEPENDENCIES
class GameObject;

//INCLUDE DEPENDENCIES
#include "Component.h"
#include "ObjectTreeNode.h"
#include "CollisionHandlers.h"

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
	void CollisionHandler(OBJECT_TYPE type, SDL_Point force);

	Handler* ObstacleCollision;
	Handler* PlayerCollision;
	Handler* BossCollision;
	Handler* ZoneCollision;
	Handler* ProjectileCollision;

	ObjectTreeNode* quad;
	SDL_Rect hitbox;
	OBJECT_TYPE type;
	bool out_of_quad;

private:
	GameObject* obj;
	SDL_Point HITBOX_OFFSET;
};

#endif //__COLLISIONCOMPONENT_H_INCLUDED__