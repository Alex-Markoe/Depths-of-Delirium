//GUARD
#ifndef __REBOUNDPROJECTILEBEHAVIOR_H_INCLUDED__
#define __REBOUNDPROJECTILEBEHAVIOR_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "ProjectileBehavior.h"

class ReboundProjectileBehavior : public ProjectileBehavior{
public:
	ReboundProjectileBehavior();
	~ReboundProjectileBehavior();
	void Update() override;
	void InitAnim() override;

private:
};

#endif //__REBOUNDPROJECTILEBEHAVIOR_H_INCLUDED__