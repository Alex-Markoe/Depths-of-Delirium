//GUARD
#ifndef __PARTICLECOMPONENT_H_INCLUDED__
#define __PARTICLECOMPONENT_H_INCLUDED__

//FORWARD DEPENDENCIES
class PhysicsComponent;
class ParticleBehavior;

//INCLUDE DEPENDENCIES
#include "Component.h"

//PARTICLE COMPONENT CLASS
//DEFINES GAMEOBJECT AS A PARTICLE WITH ATTACHABLE BEHAVIOR
class ParticleComponent : public Component {
public:
	ParticleComponent(PhysicsComponent* _physics, ParticleBehavior* _behavior);
	~ParticleComponent();
	void Update() override;
	void SetVelocity(SDL_Point _velocity);

private:
	ParticleBehavior* behavior;
};

#endif //__PARTICLECOMPONENT_H_INCLUDED__