#include "Transitioner.h"

Transitioner::Transitioner(){
	roomName = "Levels/test.level";
	setting = CAVERNS;
	roomNumber = 1;
}


Transitioner::~Transitioner()
{

}

SDL_Point Transitioner::Update(){
	int x;
	int y;

	switch (setting){
	case CAVERNS: //Transitions for caverns
		switch (roomNumber){
		case 1:
			roomName = "Levels/test.level";
			x = 50;
			y = 50;
			break;
		case 2:
			roomName = "";
			x = 0;
			y = 0;
			break;
		case 3:
			roomName = "";
			x = 0;
			y = 0;
			break;
		case 4:
			roomName = "";
			x = 0;
			y = 0;
			break;
		case 5:
			roomName = "";
			x = 0;
			y = 0;
			break;
		case 6:
			roomName = "";
			x = 0;
			y = 0;
			break;
		}
		break;
	}

	return SDL_Point{x,y};
}