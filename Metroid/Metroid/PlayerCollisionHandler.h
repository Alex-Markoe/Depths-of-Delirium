//GUARD
#ifndef __PLAYERCOLLISIONHANDLER_H_INCLUDED__
#define __PLAYERCOLLISIONHANDLER_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "CollisionHandlers.h"

//HANDLE PLAYER ON OBSTACLE INTERACTIONS
//MAKE THE PLAYER STOP WHEN HITTING AN OBSTACLE
class PlayerCollisionHandler : public Handler {
public:
	PlayerCollisionHandler() {};
	~PlayerCollisionHandler() {};

private:
	void ObstacleCollision(GameObject* other, GameObject* obj, int f_x, int f_y) override;
};

#endif //__PLAYERCOLLISIONHANDLER_H_INCLUDED__