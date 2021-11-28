//GUARD
#ifndef __POOHANDLER_H_INCLUDED__
#define __POOHANDLER_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "CollisionHandlers.h"

//HANDLE PLAYER ON OBSTACLE INTERACTIONS
//MAKE THE PLAYER STOP WHEN HITTING AN OBSTACLE
class PlayerOnObstacleHandler : public Handler {
public:
	PlayerOnObstacleHandler() {};
	~PlayerOnObstacleHandler() {};
	void Execute(GameObject* obj, int f_x, int f_y) override;
};

#endif //__POOHANDLER_H_INCLUDED__