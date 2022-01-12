//GUARD
#ifndef __PLAYERCOMPONENT_H_INCLUDED__
#define __PLAYERCOMPONENT_H_INCLUDED__

//FORWARD DEPENDENCIES
class ProjectileBehavior;
class RenderComponent;
class AnimationComponent;
class PhysicsComponent;

//INCLUDE DEPENDENCIES
#include "ProjectileManager.h"
#include "Component.h"

//HANDLE PLAYER INPUT, STATE LOGIC
//AND PROJECTILE CREATION
class PlayerComponent : public Component {
public:
	PlayerComponent(RenderComponent* _renderer, PhysicsComponent* _physics, AnimationComponent* _animator, GameObject* _obj);
	~PlayerComponent();
	void Update() override;
	void Grounded();

private:
	RenderComponent* renderer;
	PhysicsComponent* physics;
	AnimationComponent* animator;
	GameObject* obj;
	PLAYER_STATE playerState;
	PLAYER_STATE previousState;

	const Uint8 *state;
	int previous_yVelocity;
	int jump_count;

	Uint32 spell_Anim_Timer;
	Uint32 attack_Timer;
	int TERMINAL_VELOCITY = 250;
	int HORIZONTAL_VELOCITY = 350;
	int JUMP_VELOCITY = -2000;
	bool on_ground;

	void HandleInput();
	void UpdateState();
	void SpawnProjectile(ProjectileBehavior* behavior, HANDLER_TYPE type, SDL_Rect source_rect, int lifeTime, float speed);
};

#endif //__PLAYERCOMPONENT_H_INCLUDED__