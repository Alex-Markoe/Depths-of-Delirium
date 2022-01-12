//GUARD
#ifndef __PLAYERPROJECTILECOLLISIONHANDLER_H_INCLUDED__
#define __PLAYERPROJECTILECOLLISIONHANDLER_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "CollisionHandlers.h"

class PlayerProjectileCollisionHandler : public Handler {
public:
	PlayerProjectileCollisionHandler() {};
	~PlayerProjectileCollisionHandler() {};

private:
	void ObstacleCollision(GameObject* obj, int f_x, int f_y) override;
};

#endif //__PLAYERPROJECTILECOLLISIONHANDLER_H_INCLUDED__