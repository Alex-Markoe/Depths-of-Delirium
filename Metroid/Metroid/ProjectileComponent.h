//GUARD
#ifndef __PROJECTILECOMPONENT_H_INCLUDED__
#define __PROJECTILECOMPONENT_H_INCLUDED__

//FORWARD DEPENDENCIES
class ProjectileBehavior;
class PhysicsComponent;
class RenderComponent;
class AnimationComponent;

//INCLUDE DEPENDENCIES
#include "Component.h"

//MODIFIABLE PROJECTILE BEHAVIOR
class ProjectileComponent : public Component {
public:
	ProjectileComponent(int _lifeTime, PhysicsComponent* _physics, RenderComponent* _renderer, AnimationComponent* _animator, ProjectileBehavior* _behavior);
	~ProjectileComponent();
	void Update() override;

	bool active;

private:
	Uint32 activeTimer;
	ProjectileBehavior* behavior;
};

#endif //__PROJECTILECOMPONENT_H_INCLUDED__