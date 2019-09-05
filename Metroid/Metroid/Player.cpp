#include "Player.h"

//Constructor
Player::Player(SDL_Rect initPosition, SDL_Rect initSource, int hitboxOffsetX, int hitboxOffsetY) :
	GameObject(initPosition, initSource, hitboxOffsetX, hitboxOffsetY){
	playerState = Idle;
	previousState = Idle;
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
	case Run:
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
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0){
		switch(e.key.keysym.sym){
		case SDLK_w:
			playerState = Jump;
			velocity.x = 0;
			break;
		case SDLK_s:
			playerState = Duck;
			velocity.x = 0;
			break;
		case SDLK_a:
			playerState = Run;
			flipType = SDL_FLIP_HORIZONTAL;
			velocity.x -= 6;
			break;
		case SDLK_d:
			playerState = Run;
			flipType = SDL_FLIP_NONE;
			velocity.x += 6;
			break;
		case SDLK_SPACE:
			playerState = Force;
			velocity.x = 0;
			break;
		}
	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		playerState = Idle;
		velocity.x = 0;
		velocity.y = 0;
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

	//Update the position and previous state
	previousState = playerState;
}