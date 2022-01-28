#include "PlayerComponent.h"
#include "PlayerProjectileBehavior.h"
#include "ReboundProjectileBehavior.h"
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
	can_jump = true;
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
		if (state[SDL_SCANCODE_W] && can_jump) { //Jumping
			physics->ResetKinematics(false, true);
			physics->ApplyForce(0, JUMP_VELOCITY);
			can_jump = false;
			in_action = true;
			on_ground = false;
		}
		//Check to see if the player is in the air
		if (!on_ground) {
			player_state = JUMP;
			in_action = true;
		}
	}
	
	//swift form check
	if (state[SDL_SCANCODE_SPACE] && swift_cooldown == 0 && (swift_timer + 750 > SDL_GetTicks() || swift_timer == 0)) {
		player_state = SWIFT;
		swift_form = true;
		if (swift_timer == 0) {
			swift_timer = SDL_GetTicks();
			physics->ResetKinematics(true, true);
			renderer->SetFlip(SDL_FLIP_NONE);
			collider->SetHitbox({ obj->position.x, obj->position.y, 30, 30 }, { 61, 60 });
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
			SpawnProjectile(new ReboundProjectileBehavior(), nullptr, REBOUND, { 0, 36, 39, 39 }, {5, 5}, 500, 300);
			rebound_timer = SDL_GetTicks();
			in_action = true;
		}
		else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1) && attack_timer == 0) { //Firing a spell
			ParticleSystemParams params(0, 50, 500, 6, 2, 0, 50, true, false, 0.5f, 200, 0.0f, { 0, 0 }, { 18, 18 }, FIRE_PARTICLE, STRAIGHT_ACCELERATING); //set angle in method
			SpawnProjectile(new PlayerProjectileBehavior(), &params, PLAYER_PROJ, { 0, 0, 36, 36 }, {4, 4}, 500, 300);
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
		collider->SetHitbox({ obj->position.x, obj->position.y, 95, 111 }, { 20, 33 });
		physics->ResetKinematics(true, true);
		ResetJump();
		on_ground = false;
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
	previous_y_velocity = obj->position.y;
	previous_state = player_state;
}

void PlayerComponent::ResetJump() { can_jump = true; }
void PlayerComponent::OnGround() { on_ground = true; ResetJump(); }
SDL_Point PlayerComponent::GetMousePosition() {
	SDL_Point mouse_pos = { 0,0 };
	SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
	return mouse_pos;
}
float PlayerComponent::GetAngle(SDL_Point point) {
	return atan2(point.y - (obj->position.y + (obj->position.h / 2)), point.x - (obj->position.x + (obj->position.w / 2)));
}

//Fire a projectile based on the player's position and the relative angle
//towards the mouse
void PlayerComponent::SpawnProjectile(ProjectileBehavior* behavior, ParticleSystemParams* params, HANDLER_TYPE type, SDL_Rect source_rect, SDL_Point hitbox_offset, int lifeTime, int speed) {
	float angle = GetAngle(GetMousePosition());
	SDL_Point init_force = { speed * cos(angle), speed * sin(angle) };
	behavior->SetForce(init_force.x, init_force.y);
	if (params != nullptr) params->init_angle = (int)(angle * 180 / M_PI) + 180;
	ProjectileManager::instance().Add({obj->position.x + (obj->position.w / 2), obj->position.y + (obj->position.h / 2), source_rect.w, source_rect.h}, 
									  source_rect, hitbox_offset, behavior, params, type, 5, lifeTime, 50, 1.0f);

	spell_anim_timer = SDL_GetTicks();
}
//Calculate swift movement
//Follows cursor
void PlayerComponent::SwiftMovement() {
	SDL_Point mouse_pos = GetMousePosition();
	float angle = GetAngle(mouse_pos);
	int dist_x = (mouse_pos.x - (obj->position.x + (obj->position.w / 2))) * SWIFT_VELOCITY;
	int dist_y = (mouse_pos.y - (obj->position.y + (obj->position.h / 2))) * SWIFT_VELOCITY;
	physics->ResetKinematics(true, true);
	physics->ApplyForce(dist_x, dist_y);
	renderer->SetAngle(angle * 180 / M_PI);
}