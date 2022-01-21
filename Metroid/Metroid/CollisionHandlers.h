//GUARD
#ifndef __HANDLER_H_INCLUDED__
#define __HANDLER_H_INCLUDED__

//FORWARD DEPENDENCIES
class GameObject;

//INCLUDE DEPENDENCIES
#include <SDL.h>

//HANDLER BASE CLASS
//COMMAND BASED SYSTEM MEANT TO HANDLE
//COLLISION INTERACTIONS
class Handler {
public:
	Handler(){};
	~Handler(){};
	void Execute(GameObject* other, GameObject* obj, int f_x, int f_y);

protected:
	virtual void ObstacleCollision(GameObject* other, GameObject* obj, int f_x, int f_y){};
	virtual void ProjectileCollision(GameObject* other, GameObject* obj, int f_x, int f_y){};
	virtual void PlayerCollision(GameObject* other, GameObject* obj, int f_x, int f_y){};
	virtual void BossCollision(GameObject* other, GameObject* obj, int f_x, int f_y){};
	virtual void ZoneCollision(GameObject* other, GameObject* obj, int f_x, int f_y){};
};

#endif //__HANDLER_H_INCLUDED__