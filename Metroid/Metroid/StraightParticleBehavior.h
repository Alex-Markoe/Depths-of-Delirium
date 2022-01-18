//GUARD
#ifndef __STRAIGHTPARTICLEBEHAVIOR_H_INCLUDED__
#define __STRAIGHTPARTICLEBEHAVIOR_H_INCLUDED__

//FORWARD DEPENDENCIES

//INCLUDE DEPENDENCIES
#include "ParticleBehavior.h"

class StraightParticleBehavior : public ParticleBehavior {
public:
	StraightParticleBehavior();
	~StraightParticleBehavior();
	void Update() override;
};

#endif //__STRAIGHTPARTICLEBEHAVIOR_H_INCLUDED__