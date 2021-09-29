#include "CollisionComponent.h"

CollisionComponent::CollisionComponent(GameObject* _obj, SDL_Rect _position, SDL_Point hitboxOffset, OBJECT_TYPE _type) {
	HITBOX_OFFSET = hitboxOffset;
	hitbox = { _position.x + HITBOX_OFFSET.x, _position.y + HITBOX_OFFSET.y, _position.w - (HITBOX_OFFSET.x * 2), _position.h - HITBOX_OFFSET.y };
	obj = _obj;
	type = _type;
	out_of_quad = false;
}

CollisionComponent::~CollisionComponent() {
	ObstacleCollision = nullptr;
	PlayerCollision = nullptr;
	BossCollision = nullptr;
	ZoneCollision = nullptr;
	ProjectileCollision = nullptr;
	obj = nullptr;
}

void CollisionComponent::CollisionHandler(OBJECT_TYPE type, SDL_Point force) {
	switch (type) {
	case OBSTACLE:
		ObstacleCollision->execute(obj, force);
		break;
	case PROJECTILE:
		ProjectileCollision->execute(obj, force);
		break;
	case PLAYER:
		PlayerCollision->execute(obj, force);
		break;
	case BOSS:
		BossCollision->execute(obj, force);
		break;
	case ZONE:
		ZoneCollision->execute(obj, force);
		break;
	}
}

void CollisionComponent::UpdatePosition(SDL_Rect position) {
	hitbox.x = position.x + HITBOX_OFFSET.x;
	hitbox.y = position.y + HITBOX_OFFSET.y;
	if (hitbox.x + hitbox.w < quad->dimensions.x || hitbox.x > quad->dimensions.x + quad->dimensions.w ||
		hitbox.y + hitbox.h < quad->dimensions.y || hitbox.y > quad->dimensions.y + quad->dimensions.h) {
		out_of_quad = true;
	}
}

void CollisionComponent::Update() {}