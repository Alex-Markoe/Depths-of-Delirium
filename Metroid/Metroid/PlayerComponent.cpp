#include "PlayerComponent.h"
#include "PlayerProjectileBehavior.h"
#include "ParticleSystemParams.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"

//Constructor
PlayerComponent::PlayerComponent(RenderComponent* _renderer, PhysicsComponent* _physics, AnimationComponent* _animator, CollisionComponent* _collider, GameObject* _obj){
	renderer = _renderer;
	physics = _physics;
	animator = _animator;
	collider = _collider;
	obj = _obj;
	player_state = IDLE;
	previous_state = IDLE;
	state = SDL_GetKeyboardState(NULL);
	attack_timer = 0;
	rebound_timer = 0;
	swift_timer = 0;
	swift_cooldown = 0;
	jump_count = 1;
	on_ground = false;
	swift_form = false;
	active = false;
}
//Destructor
PlayerComponent::~PlayerComponent(){
	renderer = nullptr;
	physics = nullptr;
	animator = nullptr;
	obj = nullptr;
}

//Update the player's movement based on the current state
void PlayerComponent::UpdateState(){
	switch (player_state) {
	case IDLE:
		animator->SetAnimationSource(0, 0, 4, true);
		break;
	case RUN:
		animator->SetAnimationSource(0, 144, 7, true);
		break;
	case SWIFT:
		animator->SetAnimationSource(675, 0, 2, true);
		break;
	case JUMP:
		animator->SetAnimationSource(405, 288, 2, true);
		break;
	case FIRING:
		animator->SetAnimationSource(0, 288, 2, true);
		break;
	}
}

//Update the player's state then call all other update methods
void PlayerComponent::HandleInput(){
	bool in_action = false;

	//MOVEMENT LOGIC
	if (!swift_form) {
		if (state[SDL_SCANCODE_D]) { //Running right
			player_state = RUN;
			renderer->SetFlip(SDL_FLIP_NONE);
			physics->ApplyForce(HORIZONTAL_VELOCITY, 0);
			in_action = true;
		}
		else if (state[SDL_SCANCODE_A]) { //Running left
			player_state = RUN;
			renderer->SetFlip(SDL_FLIP_HORIZONTAL);
			physics->ApplyForce(-HORIZONTAL_VELOCITY, 0);
			in_action = true;
		}
		if (state[SDL_SCANCODE_W] && jump_count > 0) { //Jumping
			if (!on_ground) {
				physics->velocity_y = 0;
				physics->acceleration_y = 0;
			}
			physics->ApplyForce(0, JUMP_VELOCITY);
			jump_count--;
			in_action = true;
		}
		//Check to see if the player is in the air
		if (physics->velocity_y < 0 || physics->velocity_y > 0 || previous_yVelocity != 0) {
			player_state = JUMP;
			on_ground = false;
			in_action = true;
		}
		else {
			ResetJump();
			on_ground = true;
		}
	}
	
	//swift form check
	if (state[SDL_SCANCODE_SPACE] && swift_cooldown == 0 && (swift_timer + 750 > SDL_GetTicks() || swift_timer == 0)) {
		player_state = SWIFT;
		swift_form = true;
		if (swift_timer == 0) {
			swift_timer = SDL_GetTicks();
			physics->ResetKinematics();
			renderer->SetFlip(SDL_FLIP_NONE);
			collider->SetHitbox({72, 54, 42, 27});
		}
		in_action = true;
	}
	else {
		swift_form = false;
	}
	//MOVEMENT END
	//ACTION LOGIC
	if (!swift_form) {
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(3) && rebound_timer == 0) { //Using the force push
			SpawnProjectile(new PlayerProjectileBehavior(), nullptr, REBOUND, { 0, 21, 39, 39 }, 500, 300);
			rebound_timer = SDL_GetTicks();
			in_action = true;
		}
		else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1) && attack_timer == 0) { //Firing a spell
			ParticleSystemParams params(0, 10, 50, 20, 1, 0, 50, true, false, 1.0f, 125, 0.0f, { 0, 0 }, { 20, 0 }, FIRE_PARTICLE, STRAIGHT_ACCELERATING); //set angle in method
			SpawnProjectile(new PlayerProjectileBehavior(), &params, PLAYER_PROJ, { 0, 21, 39, 39 }, 500, 300);
			attack_timer = SDL_GetTicks();
			in_action = true;
		}
	}
	//ACTION END
	//Update Timers
	if (attack_timer > 0 && attack_timer + 500 < SDL_GetTicks()) {
		attack_timer = 0;
	}
	if (rebound_timer > 0 && rebound_timer + 500 < SDL_GetTicks()) {
		rebound_timer = 0;
	}
	if (spell_anim_timer > 0) {
		if (spell_anim_timer + 250 < SDL_GetTicks()) spell_anim_timer = 0;
		player_state = FIRING;
		in_action = true;
	}
	//Start swift cooldown
	if (swift_timer > 0 && !swift_form) {
		swift_timer = 0;
		swift_cooldown = SDL_GetTicks();
		renderer->SetAngle(0);
		collider->SetHitbox({ 20, 33, 95, 111 });
	}
	if (swift_cooldown > 0 && swift_cooldown + 750 < SDL_GetTicks()) {
		swift_cooldown = 0;
	}
	
	//Determine whether or not the player is currently idle
	if (!in_action) {
		player_state = IDLE;
	}
}

//Called every frame
void PlayerComponent::Update(){
	//Call the other update methods
	HandleInput();
	if (previous_state != player_state) {
		animator->SetFrame(0);
		UpdateState();
	}

	//Apply gravity
	physics->ApplyForce(0, TERMINAL_VELOCITY);
	if (swift_form) {
		SwiftMovement();
	}

	//Update the position and previous state
	previous_yVelocity = physics->velocity_y;
	previous_state = player_state;
}

void PlayerComponent::ResetJump() {
	jump_count = 1;
}
SDL_Point PlayerComponent::GetMousePosition() {
	SDL_Point mouse_pos = { 0,0 };
	SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
	return mouse_pos;
}
float PlayerComponent::GetAngle(SDL_Point point) {
	return atan2(point.y - obj->position.y, point.x - obj->position.x);
}

//Fire a projectile based on the player's position and the relative angle
//towards the mouse
void PlayerComponent::SpawnProjectile(ProjectileBehavior* behavior, ParticleSystemParams* params, HANDLER_TYPE type, SDL_Rect source_rect, int lifeTime, int speed) {
	float angle = GetAngle(GetMousePosition());
	SDL_Point init_force = { speed * cos(angle), speed * sin(angle) };
	behavior->SetForce(init_force.x, init_force.y);
	if (params != nullptr) params->init_angle = (int)(angle * 180 / M_PI) + 180;
	ProjectileManager::instance().Add({obj->position.x, obj->position.y, source_rect.w, source_rect.h}, source_rect, behavior, params, type, lifeTime, 50, 1.0f);

	spell_anim_timer = SDL_GetTicks();
}

void PlayerComponent::SwiftMovement() {
	SDL_Point mouse_pos = GetMousePosition();
	float angle = GetAngle(mouse_pos);
	physics->ResetKinematics();
	physics->ApplyForce(cos(angle) * SWIFT_VELOCITY, sin(angle) * SWIFT_VELOCITY);
	renderer->SetAngle(angle * 180 / M_PI);
}