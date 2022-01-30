#include "CollisionHandlers.h"
#include "GameObject.h"
#include "CollisionComponent.h"

//EXECUTE COLLISION BASED ON OBJECT TYPE
void Handler::Execute(GameObject* other, GameObject* obj, int f_x, int f_y) {
	switch (other->collider->type) {
	case PLAYER:
		PlayerCollision(other, obj, f_x, f_y);
		break;
	case BOSS:
		BossCollision(other, obj, f_x, f_y);
		break;
	case PROJECTILE:
		ProjectileCollision(other, obj, f_x, f_y);
		break;
	case OBSTACLE:
		ObstacleCollision(other, obj, f_x, f_y);
		break;
	case ZONE:
		ZoneCollision(other, obj, f_x, f_y);
		break;
	}
}