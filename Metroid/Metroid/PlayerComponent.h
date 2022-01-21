//GUARD
#ifndef __PLAYERCOMPONENT_H_INCLUDED__
#define __PLAYERCOMPONENT_H_INCLUDED__

//FORWARD DEPENDENCIES
class ProjectileBehavior;
class RenderComponent;
class AnimationComponent;
class PhysicsComponent;
class ParticleSystemParams;

//INCLUDE DEPENDENCIES
#include "Component.h"
#include "ProjectileManager.h"

//REPRESENTATION OF THE
//PLAYER'S CURRENT STATE
enum PLAYER_STATE {
	IDLE,
	JUMP,
	RUN,
	FIRING,
	RUN_FIRING,
	SWIFT
};

//HANDLE PLAYER INPUT, STATE LOGIC
//AND PROJECTILE CREATION
class PlayerComponent : public Component {
public:
	PlayerComponent(RenderComponent* _renderer, PhysicsComponent* _physics, AnimationComponent* _animator, GameObject* _obj);
	~PlayerComponent();
	void Update() override;
	void ResetJump();

private:
	RenderComponent* renderer;
	PhysicsComponent* physics;
	AnimationComponent* animator;
	GameObject* obj;
	PLAYER_STATE player_state;
	PLAYER_STATE previous_state;

	const Uint8 *state;
	int previous_yVelocity;
	int jump_count;

	Uint32 spell_anim_timer;
	Uint32 attack_timer;
	Uint32 rebound_timer;
	Uint32 swift_timer;
	Uint32 swift_cooldown;
	int TERMINAL_VELOCITY = 75;
	int HORIZONTAL_VELOCITY = 300;
	int JUMP_VELOCITY = -1000;
	int SWIFT_VELOCITY = 1300;
	bool on_ground;
	bool swift_form;
	bool active;

	SDL_Point GetMousePosition();
	float GetAngle(SDL_Point point);
	void HandleInput();
	void UpdateState();
	void SwiftMovement();
	void SpawnProjectile(ProjectileBehavior* behavior, ParticleSystemParams* params, HANDLER_TYPE type, SDL_Rect source_rect, int lifeTime, int speed);
};

#endif //__PLAYERCOMPONENT_H_INCLUDED__