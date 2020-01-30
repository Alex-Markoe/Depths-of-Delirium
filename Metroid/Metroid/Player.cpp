#include "Player.h"

//Constructor
Player::Player(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY, ProjectileManager* projManager) :
	GameObject(initPosition, initSource, hitboxOffsetX, hitboxOffsetY){
	playerState = IDLE;
	previousState = IDLE;
	state = SDL_GetKeyboardState(NULL);
	MAX_VELOCITY_Y = 10;
	MAX_VELOCITY_X = 8;
	projectiles = projManager;
	attackTimer = 0;
}

//Destructor
Player::~Player(){
	projectiles = nullptr;
}

//Update the player's movement based on the current state
void Player::UpdateFrame(){
	switch(playerState){
	case IDLE:
		setAnim(0, 0, 0);
		break;
	case RUN_LEFT:
	case RUN_RIGHT:
		setAnim(75, 0, 3);
		break;
	case ATTACK:
		setAnim(0, 78, 0);
		break;
	case JUMP:
		setAnim(225, 78, 1);
		break;
	case FALL:
		setAnim(0, 156, 3);
		break;
	case FORCE:
		setAnim(75, 78, 0);
		break;
	case DUCK:
		setAnim(150, 78, 0);
		break;
	}
}

//Update the player's state then call all other update methods
void Player::UpdateState(){
	moving = false;

	if (state[SDL_SCANCODE_D]) { //Running right
		playerState = RUN_RIGHT; 
		ApplyForce(SDL_Point{ 8 - velocity.x, 0 });
		moving = true; 
	}
	else if (state[SDL_SCANCODE_A]) { //Running left
		playerState = RUN_LEFT;
		ApplyForce(SDL_Point{ -8 - velocity.x, 0 });
		moving = true;
	}
	if (state[SDL_SCANCODE_SPACE]) { //Using the force push
		playerState = FORCE;
		moving = true;
	}
	if (state[SDL_SCANCODE_W] && !inAir) { //Jumping
		ApplyForce(SDL_Point{ 0, -10 });
		moving = true;
	}
	if (state[SDL_SCANCODE_S] && !inAir) { //Ducking
		playerState = DUCK;
		acceleration.x = 0;
		velocity.x = 0;
		moving = true;
	}
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(1) && attackTimer == 0) { //Firing a spell
		playerState = ATTACK;
		SDL_Point mousePos = {0,0};
		SDL_GetMouseState(&mousePos.x, &mousePos.y);
		float angle = atan2(mousePos.y - position.y, mousePos.x - position.x);
		SDL_Point initialForce = { 5.f * cos(angle), 5.f * sin(angle) };

		projectiles->Add(position, initialForce, FIRE, true, 0);
		attackTimer = SDL_GetTicks();
		moving = true;
	}
	
	//Check to see if the player is in the air
	if (velocity.y != 0 || p_vel_Y != 0) {
		playerState = JUMP;
		inAir = true;
		moving = true;
	}
	else
		inAir = false;

	//Determine whether or not the player is currently idle
	if (!moving) {
		playerState = IDLE;
		velocity.x = 0;
	}

	if (attackTimer > 0  && attackTimer + 500 < SDL_GetTicks())
		attackTimer = 0;
}

void Player::Update(){
	//Call the other update methods
	UpdateState();
	if (previousState != playerState) {
		frame = 0;
		stateChange = true;
		UpdateFrame();
	}
	else {
		stateChange = false;
	}

	UpdateAnimation();

	//Apply gravity
	ApplyForce(SDL_Point{ 0, TERMINAL_VELOCITY });

	//Update the position and previous state
	p_vel_Y = velocity.y;
	previousState = playerState;
}