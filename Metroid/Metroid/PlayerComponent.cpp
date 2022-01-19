#include "PlayerComponent.h"
#include "PlayerProjectileBehavior.h"
#include "ParticleSystemParams.h"
#include "GameObject.h"
#include "RenderComponent.h"

//Constructor
PlayerComponent::PlayerComponent(RenderComponent* _renderer, PhysicsComponent* _physics, AnimationComponent* _animator, GameObject* _obj){
	renderer = _renderer;
	physics = _physics;
	animator = _animator;
	obj = _obj;
	playerState = IDLE;
	previousState = IDLE;
	state = SDL_GetKeyboardState(NULL);
	attack_Timer = 0;
	jump_count = 1;
	on_ground = false;
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
	switch (playerState) {
	case IDLE:
		animator->SetAnimationSource(0, 0, 0, true);
		break;
	case RUN:
		animator->SetAnimationSource(75, 0, 3, true);
		break;
	case JUMP:
		animator->SetAnimationSource(75, 156, 1, true);
		break;
	case FIRING:
		animator->SetAnimationSource(0, 78, 0, true);
		break;
	case RUN_FIRING:
		animator->SetAnimationSource(75, 78, 3, true);
		break;
	}
}

//Update the player's state then call all other update methods
void PlayerComponent::HandleInput(){
	bool inAction = false;

	//MOVEMENT LOGIC
	if (state[SDL_SCANCODE_D]) { //Running right
		playerState = RUN; 
		renderer->SetFlip(SDL_FLIP_NONE); 
		physics->ApplyForce(HORIZONTAL_VELOCITY, 0);
		inAction = true; 
	}
	else if (state[SDL_SCANCODE_A]) { //Running left
		playerState = RUN;
		renderer->SetFlip(SDL_FLIP_HORIZONTAL);
		physics->ApplyForce(-HORIZONTAL_VELOCITY, 0);
		inAction = true;
	}
	if (state[SDL_SCANCODE_W] && jump_count > 0) { //Jumping
		physics->ApplyForce(0, JUMP_VELOCITY);
		jump_count--;
		inAction = true;
	}
	//Check to see if the player is in the air
	if (physics->velocity_y < 0 || physics->velocity_y > 0 || previous_yVelocity != 0) {
		playerState = JUMP;
		on_ground = false;
		inAction = true;
	}
	else {
		jump_count = 1;
		on_ground = true;
	}
	//MOVEMENT END
	//ACTION LOGIC
	if (attack_Timer == 0) {
		if (state[SDL_SCANCODE_SPACE]) { //Using the force push
			//attack_Timer = SDL_GetTicks();
			//inAction = true;
		}
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1)) { //Firing a spell
			ParticleSystemParams params(0, 10, 50, 20, 1, 0, 50, true, false, 1.0f, 125, 0.0f, { 0, 0 }, { 0, 0 }, FIRE_PARTICLE, STRAIGHT_ACCELERATING); //set angle in method
			SpawnProjectile(new PlayerProjectileBehavior(), &params, PLAYER_PROJ, { 0, 21, 39, 39 }, 500, 500);
			attack_Timer = SDL_GetTicks();
			inAction = true;
		}
	}
	//ACTION END
	//Update Timers
	/*if (attack_Timer > 0 && attack_Timer + 500 < SDL_GetTicks()) {
		attack_Timer = 0;
	}*/
	if (spell_Anim_Timer > 0) {
		if (spell_Anim_Timer + 250 < SDL_GetTicks()) spell_Anim_Timer = 0;
		else if (playerState == RUN) {
			playerState = RUN_FIRING;
			inAction = true;
		}
		else {
			playerState = FIRING;
			inAction = true;
		}
	}
	
	//Determine whether or not the player is currently idle
	if (!inAction) {
		playerState = IDLE;
	}
}

//Called every frame
void PlayerComponent::Update(){
	//Call the other update methods
	HandleInput();
	if (previousState != playerState) animator->SetFrame(0);
	UpdateState();

	//Apply gravity
	if (!on_ground) physics->ApplyForce(0, TERMINAL_VELOCITY);

	//Update the position and previous state
	previous_yVelocity = physics->velocity_y;
	previousState = playerState;
}

void PlayerComponent::Grounded() {
	jump_count = 1;
	on_ground = true;
}

//Fire a projectile based on the player's position and the relative angle
//towards the mouse
void PlayerComponent::SpawnProjectile(ProjectileBehavior* behavior, ParticleSystemParams* params, HANDLER_TYPE type, SDL_Rect source_rect, int lifeTime, int speed) {
	SDL_Point mouse_pos = { 0,0 };
	SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
	float angle = atan2(mouse_pos.y - obj->position.y, mouse_pos.x - obj->position.x);
	SDL_Point init_force = { speed * cos(angle), speed * sin(angle) };
	behavior->SetForce(init_force.x, init_force.y);
	if (params != nullptr) params->init_angle = (int)(angle * 180 / M_PI) + 180;
	ProjectileManager::instance().Add({obj->position.x, obj->position.y, source_rect.w, source_rect.h}, source_rect, behavior, params, type, lifeTime, 50, 1.0f);

	spell_Anim_Timer = SDL_GetTicks();
}