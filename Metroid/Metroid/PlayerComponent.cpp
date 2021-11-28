#include "PlayerComponent.h"

//Constructor
PlayerComponent::PlayerComponent(RenderComponent* _renderer, PhysicsComponent* _physics, AnimationComponent* _animator){
	renderer = _renderer;
	physics = _physics;
	animator = _animator;
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
}

//Update the player's movement based on the current state
void PlayerComponent::UpdateState(){
	switch (playerState) {
	case IDLE:
		animator->SetAnimationSource(0, 0, 0);
		break;
	case RUN:
		animator->SetAnimationSource(75, 0, 3);
		break;
	case JUMP:
		animator->SetAnimationSource(75, 156, 1);
		break;
	case FIRING:
		animator->SetAnimationSource(0, 78, 0);
		break;
	case RUN_FIRING:
		animator->SetAnimationSource(75, 78, 3);
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
		std::cout << physics->velocity_y << std::endl;
	}
	else {
		jump_count = 1;
		on_ground = true;
	}
	//MOVEMENT END
	//ACTION LOGIC
	if (attack_Timer == 0) {
		if (state[SDL_SCANCODE_SPACE]) { //Using the force push
			//SpawnProjectile(PUSH);
			attack_Timer = SDL_GetTicks();
			inAction = true;
		}
		if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1)) { //Firing a spell
			//SpawnProjectile(current_Proj_Type);
			attack_Timer = SDL_GetTicks();
			inAction = true;
		}
	}
	//ACTION END
	//Update Timers
	if (attack_Timer > 0 && attack_Timer + 500 < SDL_GetTicks()) {
		attack_Timer = 0;
	}
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
void PlayerComponent::SpawnProjectile(PROJECTILE_TYPE type) {
	/*SDL_Point mousePos = { 0,0 };
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	float angle = atan2(mousePos.y - position.y, mousePos.x - position.x);
	SDL_Point initialForce = { 5.f * cos(angle), 5.f * sin(angle) };
	projectiles->Add(SDL_Rect{position.x + (hitbox.w/2), position.y + (hitbox.h/2), 0, 0}, 
								initialForce, type, true, angle * (180.f / M_PI));

	if (mousePos.x < position.x) flipType = SDL_FLIP_HORIZONTAL;
	else flipType = SDL_FLIP_NONE;

	spell_Anim_Timer = SDL_GetTicks();*/
}