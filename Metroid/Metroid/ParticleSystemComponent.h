//GUARD
#ifndef __PARTICLESYSTEMCOMPONENT_H_INCLUDED__
#define __PARTICLESYSTEMCOMPONENT_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "Component.h"

//ATTACHABLE PARTICLE SYSTEM
class ParticleSystemComponent : public Component {
public:
	ParticleSystemComponent();
	~ParticleSystemComponent();
	void Update() override;

private:
	SDL_Point init_Speed;
	SDL_Point grav;
	Uint32 spawn_Timer;
	Uint32 system_Timer = 0;
	int init_Angle;
	int angle_Range;
	int spawn_Frequency;
	int particle_Lifetime;
	int system_Lifetime;
};

#endif //__PARTICLESYSTEMCOMPONENT_H_INCLUDED__