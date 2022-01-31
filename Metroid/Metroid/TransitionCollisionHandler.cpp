#include "TransitionCollisionHandler.h"
#include "MainScene.h"
#include "FileManager.h"

//Constructor
//next is true for going to next room, false for previous room
TransitionCollisionHandler::TransitionCollisionHandler(MainScene* _scene, bool next) {
	scene = _scene;
	if (next) room = &TransitionCollisionHandler::Next;
	else room = &TransitionCollisionHandler::Previous;
}

//Transition to next scene
void TransitionCollisionHandler::PlayerCollision(GameObject* other, GameObject* obj, int f_x, int f_y) {
	(this->*room)();
	scene->LoadLevel();
}
//Go to the next room
void TransitionCollisionHandler::Next() {
	FileManager::instance().ToNext();
}
//Go to the previous room
void TransitionCollisionHandler::Previous() {
	FileManager::instance().ToPrevious();
}
