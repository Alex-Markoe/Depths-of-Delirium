//GUARD
#ifndef __PLAYERCOMPONENT_H_INCLUDED__
#define __PLAYERCOMPONENT_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "Component.h"
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"

//HANDLE PLAYER INPUT, STATE LOGIC
//AND PROJECTILE CREATION
class PlayerComponent : public Component {
public:
	PlayerComponent(RenderComponent* _renderer, PhysicsComponent* _physics, AnimationComponent* _animator);
	~PlayerComponent();
	void Update() override;

private:
	RenderComponent* renderer;
	PhysicsComponent* physics;
	AnimationComponent* animator;
	PLAYER_STATE playerState;
	PLAYER_STATE previousState;

	const Uint8 *state;
	int previous_yVelocity;
	int jump_count;

	Uint32 spell_Anim_Timer;
	Uint32 attack_Timer;
	int TERMINAL_VELOCITY = 60;
	int HORIZONTAL_VELOCITY = 50;
	int JUMP_VELOCITY = -300;
	bool on_ground;

	void HandleInput();
	void UpdateState();
	void SpawnProjectile(PROJECTILE_TYPE type);
};

#endif //__PLAYERCOMPONENT_H_INCLUDED__