//GUARD
#ifndef __TRANSITIONCOLLISIONHANDLER_H_INCLUDED__
#define __TRANSITIONCOLLISIONHANDLER_H_INCLUDED__

//FORWARD DEPENDENCIES
class MainScene;

//INCLUDE DEPENDENCIES
#include "CollisionHandlers.h"

//HANDLES TRANSITION TO NEW ROOM 
//WHEN THE PLAYER COLLIDIES WITH IT
class TransitionCollisionHandler :	public Handler{
public:
	TransitionCollisionHandler(MainScene* _scene, bool next);
	~TransitionCollisionHandler(){};

private:
	void PlayerCollision(GameObject* other, GameObject* obj, int f_x, int f_y) override;
	void Next();
	void Previous();

	MainScene* scene;
	void (TransitionCollisionHandler::*room)();
};

#endif //__TRANSITIONCOLLISIONHANDLER_H_INCLUDED__