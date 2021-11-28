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
		for (int i = 0; i < 4; i++) {
			Clear(quad->quads[i]);
		}
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
	SDL_Rect item_hitbox;
	bool collide_y;

	//Iterate through each gameobject in the quad and 
	//check to see if it is colliding with the 
	//referenced object
	for (unsigned i = 0; i < quad->items.size(); i++) {
		item_hitbox = quad->items[i]->collider->hitbox;
		collide_y = false;

		//Check the y direction
		//See if the references's x dimensions are within
		//the item's x dimensions
		if ((hitbox.x > item_hitbox.x && hitbox.x < item_hitbox.x + item_hitbox.w)
			|| (hitbox.w < item_hitbox.x + item_hitbox.w && hitbox.w > item_hitbox.x)) {
			//Get the speed of the reference and then see how far it is going
			//to be in the current item
			int accel_y =  reference->physics->acceleration_y * deltaTime;
			int vel_y = reference->physics->velocity_y;
			int depth_ascending = hitbox.y - (item_hitbox.h + item_hitbox.y);
			int depth_descending = hitbox.h - item_hitbox.y;

			//Check if the descending and ascending depths
			//are within range of a collision
			if (depth_descending + (accel_y + vel_y) > 0 && depth_descending + (accel_y + vel_y) < MAX_DEPTH_Y) { //descending
				int force = GetForce(deltaTime, -depth_descending, -accel_y, -vel_y);
				//depth_descending /= deltaTime;
				reference->collider->CollisionHandler(quad->items[i]->collider->type, 0, force);
				collide_y = true;
			}
			else if (depth_ascending + (accel_y + vel_y) < 0 && depth_ascending + (accel_y + vel_y) > -MAX_DEPTH_Y) { //ascending
				int force = GetForce(deltaTime, -depth_ascending, -accel_y, -vel_y);
				//depth_ascending /= deltaTime;
				reference->collider->CollisionHandler(quad->items[i]->collider->type, 0, force);
				collide_y = true;
			}
		}
		//if (collide_y) continue;
		//Check the x direction
		//Check if the reference's y dimensions are within
		//the item's y dimensions
		if ((hitbox.y < item_hitbox.y && hitbox.h > item_hitbox.y)
			|| (hitbox.y < item_hitbox.y + item_hitbox.h && hitbox.h > item_hitbox.y + item_hitbox.h)) {
			//Get the speed of the reference and then see how far it is going
			// to be in the current item
			int accel_x = reference->physics->acceleration_x * deltaTime;
			int vel_x = reference->physics->velocity_x;
			int depth_left = hitbox.x - (item_hitbox.w + item_hitbox.x);
			int depth_right = hitbox.w - item_hitbox.x;

			//Check if the left and right depths are 
			//within range of a collision
			if (depth_left + (accel_x + vel_x) < 0 && depth_left + (accel_x + vel_x) > -MAX_DEPTH_X) { //left
				int force = GetForce(deltaTime, -depth_left, -accel_x, -vel_x);
				reference->collider->CollisionHandler(quad->items[i]->collider->type, force, 0);
			}
			else if (depth_right + (accel_x + vel_x) > 0 && depth_right + (accel_x + vel_x) < MAX_DEPTH_X) { //right
				int force = GetForce(deltaTime, -depth_right, -accel_x, -vel_x);
				reference->collider->CollisionHandler(quad->items[i]->collider->type, force, 0);
			}
		}
	}

	//Check the next quadrant
	if (quad->quads[0] != NULL){
		for (int i = 0; i < 4; i++) {
			if (InBounds(collisionSpace, quad->quads[i]->dimensions)) {
				BoxCollisionDetector(reference, quad->quads[i], collisionSpace, hitbox, deltaTime);
			}
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
			reference->collider->CollisionHandler(quad->items[i]->collider->type, 0, 0);
		}
	}

	//Check the next quadrant
	if (quad->quads[0] != NULL) {
		for (int i = 0; i < 4; i++) {
			if (InBounds(collisionSpace, quad->quads[i]->dimensions)) {
				CircleCollisionDetector(reference, quad->quads[i], collisionSpace, hitbox, deltaTime);
			}
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
//Helper function
//Return the force required to resolve
//a collision
int GetForce(float deltaTime, int depth, int accel, int vel) {
	int speed = (accel + vel) / deltaTime;
	return (depth / deltaTime) + speed;
}