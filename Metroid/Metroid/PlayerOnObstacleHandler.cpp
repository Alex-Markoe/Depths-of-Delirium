#include "PlayerOnObstacleHandler.h"
#include "GameObject.h"

void PlayerOnObstacleHandler::Execute(GameObject* obj, float f_x, float f_y) {
	obj->physics->ApplyForce(f_x, f_y);
}