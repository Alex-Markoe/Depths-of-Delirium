//GUARD
#ifndef __ICEWHEELPROJECTILEBEHAVIOR_H_INCLUDED__
#define __ICEWHEELPROJECTILEBEHAVIOR_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "ProjectileBehavior.h"

class IceWheelProjectileBehavior : public ProjectileBehavior {
public:
	IceWheelProjectileBehavior();
	~IceWheelProjectileBehavior();
	void Update() override;
	void InitAnim() override;

private:

};

#endif //__ICEWHEELPROJECTILEBEHAVIOR_H_INCLUDED__