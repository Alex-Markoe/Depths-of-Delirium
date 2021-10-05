#include "PlayerOnObstacleHandler.h"
#include "GameObject.h"

void PlayerOnObstacleHandler::Execute(GameObject* obj, SDL_Point force) {
	obj->physics->ApplyForce(force);
}