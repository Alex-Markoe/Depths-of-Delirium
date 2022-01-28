//GUARD
#ifndef __ICEWHEELCOLLISIONHANDLER_H_INCLUDED__
#define __ICEWHEELCOLLISIONHANDLER_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "CollisionHandlers.h"

class IceWheelCollisionHandler : public Handler {
public:
	IceWheelCollisionHandler() {};
	~IceWheelCollisionHandler() {};

private:
	void ObstacleCollision(GameObject* other, GameObject* obj, int f_x, int f_y) override;
};

#endif //__ICEWHEELCOLLISIONHANDLER_H_INCLUDED__