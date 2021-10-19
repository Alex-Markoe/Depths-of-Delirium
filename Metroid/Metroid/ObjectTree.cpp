#include "ObjectTree.h"
#include "GameObject.h"

//Constructor
void ObjectTree::Init(int levelWidth, int levelHeight) {
	head = new ObjectTreeNode(SDL_Rect{ 0, 0, levelWidth, levelHeight });
	Divide(2, head);
}
//Divide the tree based on a given number of iterations
void ObjectTree::Divide(int iterations, ObjectTreeNode* quad) {
	iterations--;
	quad->Divide();
	if (iterations > 0) {
		for (unsigned i = 0; i < 4; i++) {
			Divide(iterations, quad->quads[i]);
		}
	}
}

//Constructor
ObjectTree::ObjectTree(int levelWidth, int levelHeight){
	Init(levelWidth, levelHeight);
}
//Destructor
ObjectTree::~ObjectTree(){
	delete head;
}

//Remove all nodes from the tree
void ObjectTree::Reset(int levelWidth, int levelHeight) {
	delete head;
	Init(levelWidth, levelHeight);
}
//Clears all objects out of the tree
void ObjectTree::Clear() {
	Clear(head);
}
void ObjectTree::Clear(ObjectTreeNode* quad) {
	if (quad->quads[0] != NULL) {
		Clear(quad->quads[0]);
		Clear(quad->quads[1]);
		Clear(quad->quads[2]);
		Clear(quad->quads[3]);
	}
	quad->items.clear();
}

//Public version of the add method
void ObjectTree::Add(GameObject* item){
	Add(item, head);
}
//Private version of the add method that uses
//recursion to find the next best quad
void ObjectTree::Add(GameObject* item, ObjectTreeNode* quad){
	if (quad->quads[0] == NULL){
		quad->items.push_back(item);
		item->collider->quad = quad;
	}
	else{
		SDL_Rect hitbox = item->collider->hitbox;
		if (InQuad(hitbox, quad->quads[0]->dimensions)){
			Add(item, quad->quads[0]);
		}
		else if (InQuad(hitbox, quad->quads[1]->dimensions)){
			Add(item, quad->quads[1]);
		}
		else if (InQuad(hitbox, quad->quads[2]->dimensions)){
			Add(item, quad->quads[2]);
		}
		else if (InQuad(hitbox, quad->quads[3]->dimensions)){
			Add(item, quad->quads[3]);
		}
		else{
			quad->items.push_back(item);
		}
	}
}

//Detect collision based on box collider
void ObjectTree::BoxCollisionDetector(GameObject* reference, float deltaTime) {
	//Bounds of possible collision quadrants
	int collX = reference->collider->hitbox.x - MAX_COLLISION_DIST_X;
	int collY = reference->collider->hitbox.y - MAX_COLLISION_DIST_Y;
	int collW = reference->collider->hitbox.w + reference->collider->hitbox.x + MAX_COLLISION_DIST_X;
	int collH = reference->collider->hitbox.h + reference->collider->hitbox.y + MAX_COLLISION_DIST_Y;

	//reference hitbox
	int x = reference->collider->hitbox.x;
	int y = reference->collider->hitbox.y;
	int width = reference->collider->hitbox.x + reference->collider->hitbox.w;
	int height = reference->collider->hitbox.y + reference->collider->hitbox.h;

	//reference type

	if (head != NULL)
		BoxCollisionDetector(reference, head, SDL_Rect{ collX, collY, collW, collH }, SDL_Rect{ x, y, width, height }, deltaTime);
}
//determine if the referenced object is colliding with any objects in its relevant quads
void ObjectTree::BoxCollisionDetector(GameObject* reference, ObjectTreeNode* quad, SDL_Rect collisionSpace, SDL_Rect hitbox, float deltaTime){
	//Loop through each object in the quad
	SDL_Rect item_hitbox;
	for (unsigned i = 0; i < quad->items.size(); i++) {
		item_hitbox = quad->items[i]->collider->hitbox;

		//Check the x direction
		if ((hitbox.y < item_hitbox.y && hitbox.h > item_hitbox.y)
			|| (hitbox.y < item_hitbox.y + item_hitbox.h && hitbox.h > item_hitbox.y + item_hitbox.h)) {
			int speed_x = reference->physics->velocity_x + reference->physics->acceleration_x;
			int depth_left = hitbox.x - (item_hitbox.w + item_hitbox.x);
			int depth_right = hitbox.w - item_hitbox.x;
			if (depth_left <= 0 && depth_left + (speed_x * deltaTime) > -MAX_DEPTH_X) //left
				reference->collider->CollisionHandler(quad->items[i]->collider->type, SDL_Point{ depth_left - speed_x, 0 });
			else if (depth_right >= 0 && depth_right + (speed_x * deltaTime) < MAX_DEPTH_X) //right
				reference->collider->CollisionHandler(quad->items[i]->collider->type, SDL_Point{ depth_right - speed_x, 0 });
		}

		//Check the y direction
		if ((hitbox.x > item_hitbox.x && hitbox.x < item_hitbox.x + item_hitbox.w)
			|| (hitbox.w < item_hitbox.x + item_hitbox.w && hitbox.w > item_hitbox.x)) {
			int speed_y = reference->physics->velocity_y + reference->physics->acceleration_y;
			int depth_top = hitbox.y - (item_hitbox.h + item_hitbox.y);
			int depth_bottom = hitbox.h - item_hitbox.y;
			if (depth_bottom >= 0 && depth_bottom + (speed_y * deltaTime) < MAX_DEPTH_Y) //descending
				reference->collider->CollisionHandler(quad->items[i]->collider->type, SDL_Point{ 0, -depth_bottom - speed_y});
			else if (depth_top <= 0 && depth_top + (speed_y * deltaTime) > -MAX_DEPTH_Y) //ascending
				reference->collider->CollisionHandler(quad->items[i]->collider->type, SDL_Point{ 0, depth_top - speed_y});
		}
	}

	//Check the next quadrant
	if (quad->quads[0] != NULL){
		if (InBounds(collisionSpace, quad->quads[0]->dimensions)) {
			BoxCollisionDetector(reference, quad->quads[0], collisionSpace, hitbox, deltaTime);
		}
		if (InBounds(collisionSpace, quad->quads[1]->dimensions)) {
			BoxCollisionDetector(reference, quad->quads[1], collisionSpace, hitbox, deltaTime);
		}
		if (InBounds(collisionSpace, quad->quads[2]->dimensions)) {
			BoxCollisionDetector(reference, quad->quads[2], collisionSpace, hitbox, deltaTime);
		}
		if (InBounds(collisionSpace, quad->quads[3]->dimensions)) {
			BoxCollisionDetector(reference, quad->quads[3], collisionSpace, hitbox, deltaTime);
		}
	}
}

//Detect collision based on hitbox center
void ObjectTree::CircleCollisionDetector(GameObject* reference, float deltaTime) {
	int width = reference->collider->hitbox.w / 2;
	int height = reference->collider->hitbox.h / 2;
	int centerX = reference->collider->hitbox.x + width;
	int centerY = reference->collider->hitbox.y + height;

	int collX = centerX - width - MAX_COLLISION_DIST_X;
	int collY = centerY - height - MAX_COLLISION_DIST_Y;
	int collW = centerX + width + MAX_COLLISION_DIST_X;
	int collH = centerY + height + MAX_COLLISION_DIST_Y;

	if (head != NULL)
		CircleCollisionDetector(reference, head, SDL_Rect{ collX, collY, collW, collH }, SDL_Rect{ centerX, centerY, width, height }, deltaTime);
}
//Determine if a projectile is currently colliding with a wall
void ObjectTree::CircleCollisionDetector(GameObject* reference, ObjectTreeNode* quad, SDL_Rect collisionSpace, SDL_Rect hitbox, float deltaTime) {
	SDL_Rect item_hitbox;
	int item_centerX, item_centerY, half_width, half_height;
	for (unsigned i = 0; i < quad->items.size(); i++) {
		item_hitbox = quad->items[i]->collider->hitbox;
		half_width = item_hitbox.w / 2;
		half_height = item_hitbox.h / 2;
		item_centerX = item_hitbox.x + half_width;
		item_centerY = item_hitbox.y + half_height;
		//Check distance between centers
		float distance = sqrt(pow(hitbox.x - item_centerX, 2) + pow(hitbox.y - item_centerY, 2));
		float distance_total = sqrt(pow(hitbox.w + half_width, 2) + pow(hitbox.h + half_height, 2));

		if (distance < distance_total){
			reference->collider->CollisionHandler(quad->items[i]->collider->type, SDL_Point{ 0, 0 });
		}
	}

	//Check the next quadrant
	if (quad->quads[0] != NULL) {
		if (InBounds(collisionSpace, quad->quads[0]->dimensions)) {
			CircleCollisionDetector(reference, quad->quads[0], collisionSpace, hitbox, deltaTime);
		}
		if (InBounds(collisionSpace, quad->quads[1]->dimensions)) {
			CircleCollisionDetector(reference, quad->quads[1], collisionSpace, hitbox, deltaTime);
		}
		if (InBounds(collisionSpace, quad->quads[2]->dimensions)) {
			CircleCollisionDetector(reference, quad->quads[2], collisionSpace, hitbox, deltaTime);
		}
		if (InBounds(collisionSpace, quad->quads[3]->dimensions)) {
			CircleCollisionDetector(reference, quad->quads[3], collisionSpace, hitbox, deltaTime);
		}
	}
}

//Helper function
//Check if an object is within relevant bounds of an adjacent quadrant
bool InBounds(SDL_Rect in_rect, SDL_Rect encapsulating_rect) {
	return ((in_rect.x >= encapsulating_rect.x && in_rect.x <= encapsulating_rect.x + encapsulating_rect.w)
		   || (in_rect.w >= encapsulating_rect.x && in_rect.w <= encapsulating_rect.x + encapsulating_rect.w)) &&
		   ((in_rect.y >= encapsulating_rect.y && in_rect.y <= encapsulating_rect.y + encapsulating_rect.h)
		   || (in_rect.h >= encapsulating_rect.y && in_rect.h <= encapsulating_rect.y + encapsulating_rect.h));
}
//Helper function
//Check if object is completely contained in quadrant
bool InQuad(SDL_Rect hitbox, SDL_Rect quad) {
	return hitbox.x >= quad.x &&
		   hitbox.x + hitbox.w <= quad.w + quad.x &&
		   hitbox.y >= quad.y &&
		   hitbox.y + hitbox.h <= quad.h + quad.y;
}