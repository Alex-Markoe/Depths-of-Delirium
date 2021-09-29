#include "PlayerOnObstacleHandler.h"
#include "GameObject.h"

void PlayerOnObstacleHandler::execute(GameObject* obj, SDL_Point force) {
	obj->physics->ApplyForce(force);
}