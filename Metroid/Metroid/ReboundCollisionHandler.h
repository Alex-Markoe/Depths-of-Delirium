//GUARD
#ifndef __REBOUNDCOLLISIONHANDLER_H_INCLUDED__
#define __REBOUNDCOLLISIONHANDLER_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "CollisionHandlers.h"

//COLLISION HANDLER SPECIFIC TO THE PLAYER 
//REBOUND PROJECTILE
class ReboundCollisionHandler : public Handler {
public:
	ReboundCollisionHandler() {};
	~ReboundCollisionHandler();
	void SetPlayer(GameObject* _player);

private:
	void ApplyBounce(GameObject* obj);
	void ObstacleCollision(GameObject* other, GameObject* obj, int f_x, int f_y) override;

	GameObject* player;
};

#endif //__REBOUNDCOLLISIONHANDLER_H_INCLUDED__