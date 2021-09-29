//GUARD
#ifndef __PROJECTILECOMPONENT_H_INCLUDED__
#define __PROJECTILECOMPONENT_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "Component.h"

//MODIFIABLE PROJECTILE BEHAVIOR
class ProjectileComponent : public Component {
public:
	ProjectileComponent();
	~ProjectileComponent();
	void Update() override;

	PROJECTILE_TYPE proj_Type;
	bool active;
	bool playerOwned;

private:
	SDL_Point init_Force;
	Uint32 activeTimer;
	float initAngle;
};

#endif //__PROJECTILECOMPONENT_H_INCLUDED__