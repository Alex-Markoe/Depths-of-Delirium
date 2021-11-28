#include "PlayerOnObstacleHandler.h"
#include "GameObject.h"

void PlayerOnObstacleHandler::Execute(GameObject* obj, int f_x, int f_y) {
	obj->physics->ApplyForce(f_x, f_y);
}