//GUARD
#ifndef __REBOUNDPROJECTILEBEHAVIOR_H_INCLUDED__
#define __REBOUNDPROJECTILEBEHAVIOR_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "ProjectileBehavior.h"

//BEHAVIOR FOR THE 
//PLAYER REBOUND PROJECTILE
class ReboundProjectileBehavior : public ProjectileBehavior{
public:
	ReboundProjectileBehavior();
	~ReboundProjectileBehavior();
	void Update() override;
	void InitAnim() override;
	void BeginDeath() override;
};

#endif //__REBOUNDPROJECTILEBEHAVIOR_H_INCLUDED__