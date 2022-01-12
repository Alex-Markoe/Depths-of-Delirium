//GUARD
#ifndef __PLAYERPROJECTILEBEHAVIOR_H_INCLUDED__
#define __PLAYERPROJECTILEBEHAVIOR_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "ProjectileBehavior.h"

//BASIC PLAYER DAMAGE PROJECTILE
//HANDLE STUFF
class PlayerProjectileBehavior : public ProjectileBehavior {
public:
	PlayerProjectileBehavior();
	~PlayerProjectileBehavior();
	void Update() override;
	void InitAnim() override;

private:

};

#endif //__PLAYERPROJECTILEBEHAVIOR_H_INCLUDED__