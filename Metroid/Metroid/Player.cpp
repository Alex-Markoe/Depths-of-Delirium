#include "Player.h"

//Constructor
Player::Player(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY) :
	GameObject(initPosition, initSource, hitboxOffsetX, hitboxOffsetY){
	playerState = Idle;
	previousState = Idle;
	state = SDL_GetKeyboardState(NULL);
	MAX_VELOCITY_Y = 10;
	MAX_VELOCITY_X = 8;
}

//Destructor
Player::~Player(){

}

//Update the player's movement based on the current state
void Player::UpdateFrame(){
	switch(playerState){
	case Idle:
		setAnim(0, 0, 0);
		break;
	case RunLeft:
	case RunRight:
		setAnim(75, 0, 3);
		break;
	case Attack:
		setAnim(0, 78, 0);
		break;
	case Jump:
		setAnim(225, 78, 1);
		break;
	case Fall:
		setAnim(0, 156, 3);
		break;
	case Force:
		setAnim(75, 78, 0);
		break;
	case Duck:
		setAnim(150, 78, 0);
		break;
	}
}

//Update the player's state then call all other update methods
void Player::UpdateState(){
	moving = false;

	if (state[SDL_SCANCODE_D]) { //Running right
		playerState = RunRight; 
		ApplyForce(SDL_Point{ 8 - velocity.x, 0 });
		moving = true; 
	}
	else if (state[SDL_SCANCODE_A]) { //Running left
		playerState = RunLeft;
		ApplyForce(SDL_Point{ -8 - velocity.x, 0 });
		moving = true;
	}
	if (state[SDL_SCANCODE_SPACE]) { //Using the force push
		playerState = Force;
		moving = true;
	}
	if (state[SDL_SCANCODE_W] && !inAir) { //Jumping
		ApplyForce(SDL_Point{ 0, -10 });
		moving = true;
	}
	if (state[SDL_SCANCODE_S] && !inAir) { //Ducking
		playerState = Duck;
		acceleration.x = 0;
		velocity.x = 0;
		moving = true;
	}

	//Check to see if the player is in the air
	if (velocity.y != 0 || p_vel_Y != 0) {
		playerState = Jump;
		inAir = true;
		moving = true;
	}
	else
		inAir = false;

	//Determine whether or not the player is currently idle
	if (!moving) {
		playerState = Idle;
		velocity.x = 0;
	}
}

void Player::Update(){
	//Call the other update methods
	UpdateState();
	if (previousState != playerState) {
		frame = 0;
		stateChange = true;
	}
	else {
		stateChange = false;
	}

	UpdateFrame();
	UpdateAnimation();

	//Apply gravity
	ApplyForce(SDL_Point{ 0, TERMINAL_VELOCITY });

	//Update the position and previous state
	p_vel_Y = velocity.y;
	previousState = playerState;
}