//GUARD
#ifndef __ICEWHEELPROJECTILEBEHAVIOR_H_INCLUDED__
#define __ICEWHEELPROJECTILEBEHAVIOR_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "ProjectileBehavior.h"

//ICE WHEEL PROJECTILE FOR 
//ICE BOSS, ROLLS AROUND EDGES OF ARENA
class IceWheelProjectileBehavior : public ProjectileBehavior {
public:
	IceWheelProjectileBehavior();
	~IceWheelProjectileBehavior();
	void Update() override;
	void InitAnim() override;
};

#endif //__ICEWHEELPROJECTILEBEHAVIOR_H_INCLUDED__