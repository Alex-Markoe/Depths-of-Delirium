#include "Player.h"

//Constructor
Player::Player(SDL_Rect initPosition, SDL_Rect initSource, SDL_Point hitboxOffset, ProjectileManager* projManager) :
	GameObject(initPosition, initSource, hitboxOffset){
	playerState = IDLE;
	previousState = IDLE;
	state = SDL_GetKeyboardState(NULL);
	MAX_VELOCITY.y = 15;
	MAX_VELOCITY.x = 8;
	projectiles = projManager;
	attack_Timer = 0;
	current_Proj_Type = FIRE;
}

//Destructor
Player::~Player(){
	projectiles = nullptr;
}

//Update the player's movement based on the current state
void Player::UpdateFrame(){
	if (spell_Anim_Timer > 0 && playerState != RUN) 
		SetAnim(0, 78, 0);
	else {
		switch (playerState) {
		case IDLE:
			SetAnim(0, 0, 0);
			break;
		case RUN:
			if (spell_Anim_Timer == 0) SetAnim(75, 0, 3);
			else SetAnim(75, 78, 3);
			break;
		case JUMP:
			SetAnim(75, 156, 1);
			break;
		case FALL:
			SetAnim(0, 156, 3);
			break;
		case DUCK:
			SetAnim(0, 156, 0);
			break;
		}
	}
}

//Update the player's state then call all other update methods
void Player::UpdateState(){
	bool inAction = false;

	if (state[SDL_SCANCODE_D]) { //Running right
		playerState = RUN; 
		ApplyForce(SDL_Point{ 8 - velocity.x, 0 });
		inAction = true; 
	}
	else if (state[SDL_SCANCODE_A]) { //Running left
		playerState = RUN;
		ApplyForce(SDL_Point{ -8 - velocity.x, 0 });
		inAction = true;
	}
	if (state[SDL_SCANCODE_SPACE] && attack_Timer == 0) { //Using the force push
		SpawnProjectile(PUSH);
		attack_Timer = SDL_GetTicks();
		inAction = true;
	}
	if (state[SDL_SCANCODE_W] && !inAir) { //Jumping
		ApplyForce(SDL_Point{ 0, -10 });
		inAction = true;
	}
	if (state[SDL_SCANCODE_S] && !inAir) { //Ducking
		playerState = DUCK;
		acceleration.x = 0;
		velocity.x = 0;
		inAction = true;
	}
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1) && attack_Timer == 0) { //Firing a spell
		SpawnProjectile(current_Proj_Type);
		attack_Timer = SDL_GetTicks();
		inAction = true;
	}
	
	//Check to see if the player is in the air
	if (velocity.y != 0 || p_vel_Y != 0) {
		playerState = JUMP;
		inAir = true;
		inAction = true;
	}
	else
		inAir = false;

	if (attack_Timer > 0 && attack_Timer + 500 < SDL_GetTicks()) {
		attack_Timer = 0;
		pushed = false;
	}
	if (spell_Anim_Timer > 0 && spell_Anim_Timer + 250 < SDL_GetTicks()) spell_Anim_Timer = 0;

	//Determine whether or not the player is currently idle
	if (!inAction) {
		playerState = IDLE;
		if (!pushed) velocity.x = 0;
	}
}

//Called every frame
void Player::Update(){
	//Call the other update methods
	if (velocity.x < 0) flipType = SDL_FLIP_HORIZONTAL;
	else if (velocity.x > 0) flipType = SDL_FLIP_NONE;

	UpdateState();
	if (previousState != playerState) frame = 0;
	UpdateFrame();
	UpdateAnimation();

	//Apply gravity
	ApplyForce(SDL_Point{ 0, TERMINAL_VELOCITY });

	//Update the position and previous state
	p_vel_Y = velocity.y;
	previousState = playerState;
}

//Fire a projectile based on the player's position and the relative angle
//towards the mouse
void Player::SpawnProjectile(PROJECTILE_TYPE type) {
	SDL_Point mousePos = { 0,0 };
	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	float angle = atan2(mousePos.y - position.y, mousePos.x - position.x);
	SDL_Point initialForce = { 5.f * cos(angle), 5.f * sin(angle) };
	projectiles->Add(SDL_Rect{position.x + (hitbox.w/2), position.y + (hitbox.h/2), 0, 0}, 
								initialForce, type, true, angle * (180.f / M_PI));

	if (mousePos.x < position.x) flipType = SDL_FLIP_HORIZONTAL;
	else flipType = SDL_FLIP_NONE;

	spell_Anim_Timer = SDL_GetTicks();
}

//Apply the force push and ensure the player will move
void Player::ApplyPush(SDL_Point force) {
	ApplyForce(force);
	pushed = true;
}