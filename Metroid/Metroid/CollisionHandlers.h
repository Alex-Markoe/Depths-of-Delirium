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
	void Execute(int type, GameObject* obj, int f_x, int f_y){
		switch (type) {
		case 0:
			PlayerCollision(obj, f_x, f_y);
			break;
		case 1:
			BossCollision(obj, f_x, f_y);
			break;
		case 2:
			ProjectileCollision(obj, f_x, f_y);
			break;
		case 3:
			ObstacleCollision(obj, f_x, f_y);
			break;
		case 4:
			ZoneCollision(obj, f_x, f_y);
			break;
		}
	};

protected:
	virtual void ObstacleCollision(GameObject* obj, int f_x, int f_y){};
	virtual void ProjectileCollision(GameObject* obj, int f_x, int f_y){};
	virtual void PlayerCollision(GameObject* obj, int f_x, int f_y){};
	virtual void BossCollision(GameObject* obj, int f_x, int f_y){};
	virtual void ZoneCollision(GameObject* obj, int f_x, int f_y){};
};

#endif //__HANDLER_H_INCLUDED__