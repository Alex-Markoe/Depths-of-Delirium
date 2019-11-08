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
void Player::UpdateState(SDL_Event& e){
	bool moving = false;

	if (velocity.y != 0)
		inAir = true;
	else
		inAir = false;

	if (state[SDL_SCANCODE_D]) { //Running right
		playerState = RunRight; 
		ApplyForce(SDL_Point{ 7, 0 });
		moving = true; 
	}
	else if (state[SDL_SCANCODE_A]) { //Running left
		playerState = RunLeft;
		ApplyForce(SDL_Point{ -7, 0 });
		moving = true;
	}
	if (state[SDL_SCANCODE_SPACE]) { //Using the force push
		playerState = Force;
		moving = true;
	}
	if (state[SDL_SCANCODE_W] && !inAir) { //Jumping
		playerState = Jump;
		ApplyForce(SDL_Point{ 0, -10 });
		moving = true;
	}
	if (state[SDL_SCANCODE_S] && !inAir) { //Ducking
		playerState = Duck;
		velocity.x = 0;
		moving = true;
	}
	if (inAir) {
		playerState = Jump;
		moving = true;
	}
	if (!moving) {
		playerState = Idle;
		velocity.x = 0;
	}
}

void Player::Update(){
	//Check if the state has changed and reset the frame if so
	if (previousState != playerState) {
		frame = 0;
		stateChange = true;
	}
	else{
		stateChange = false;
	}

	//Call the other update methods
	UpdateAnimation();
	UpdateFrame();

	//Apply gravity
	ApplyForce(SDL_Point{ 0, TERMINAL_VELOCITY });

	//Update the position and previous state
	previousState = playerState;
}