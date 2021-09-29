#pragma once
//GUARD
#ifndef __HANDLER_H_INCLUDED__
#define __HANDLER_H_INCLUDED__

//FORWARD DEPENDENCIES
class GameObject;

//INCLUDE DEPENDENCIES
#include <SDL.h>

//HANDLER BASE CLASS
//COMMAND BASED SYSTEM MEANT TO HANDLE
//COLLISION INTERACTIONS
class Handler {
public:
	Handler(){};
	~Handler(){};
	virtual void execute(GameObject* obj, SDL_Point force){};
};

#endif //__HANDLER_H_INCLUDED__