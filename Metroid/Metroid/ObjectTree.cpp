#include "ObjectTree.h"
#include "GameObject.h"
#include "CollisionComponent.h"
#include "PhysicsComponent.h"
#include <algorithm>

//Initialize tree
void ObjectTree::Init(int levelWidth, int levelHeight) {
	head = new ObjectTreeNode(SDL_Rect{ 0, 0, levelWidth, levelHeight });
	Divide(2, head); //Do 2 iterations, should be fine :)
}
//Divide the tree based on a given number of iterations
void ObjectTree::Divide(int iterations, ObjectTreeNode* quad) {
	iterations--;
	quad->Divide();
	//Divide further if possible
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
	delete head; //recursively deletes
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
//Recursive version, clears out items if possible
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
	//If at leaf, add it to the quad
	if (quad->quads[0] == NULL){
		quad->Add(item);
	}
	else{
		//Check to see that item fits perfection in quadrant
		//if not just add it to the current quad
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
			quad->Add(item);
		}
	}
}

//Detect collision based on box collider
//Public version
void ObjectTree::BoxCollisionDetector(GameObject* reference, float deltaTime) {
	if (head != NULL || reference->collider == nullptr || reference->collider->inactive) {
		BoxCollisionDetector(reference, head, deltaTime);
	}
}
//Private version
//determine if the referenced object is colliding with any objects in its relevant quads
void ObjectTree::BoxCollisionDetector(GameObject* reference, ObjectTreeNode* quad, float deltaTime){
	//Hitbox for object that is being checked against
	SDL_Rect item_hitbox;
	//hitbox for object that is checking
	SDL_Rect hitbox = reference->collider->hitbox;

	//Iterate through each gameobject in the quad and 
	//check to see if it is colliding with the 
	//referenced object
	for (unsigned i = 0; i < quad->items.size(); i++) {
		//Don't check item with itself
		if (reference == quad->items[i] || quad->items[i]->collider == nullptr || quad->items[i]->collider->inactive) continue;
		item_hitbox = quad->items[i]->collider->hitbox; //Update hitboxes
		hitbox = reference->collider->hitbox;

		//Check if colliding, and get the depth
		//AABB collision
		if (item_hitbox.x < hitbox.x + hitbox.w && item_hitbox.x + item_hitbox.w > hitbox.x && item_hitbox.y < hitbox.y + hitbox.h && item_hitbox.y + item_hitbox.h > hitbox.y) {
			int depth_ascending = hitbox.y - (item_hitbox.h + item_hitbox.y);
			int depth_descending = (hitbox.h + hitbox.y) - item_hitbox.y;
			int depth_y = abs(depth_ascending) < depth_descending ? depth_ascending : depth_descending; //Get the shallow axis in the y
			int depth_left = hitbox.x - (item_hitbox.w + item_hitbox.x);
			int depth_right = (hitbox.w + hitbox.x) - item_hitbox.x;
			int depth_x = abs(depth_left) < depth_right ? depth_left : depth_right; //Get the shallow axis in the x
			reference->collider->CollisionHandler(quad->items[i], depth_x, depth_y);
		}
	}

	//Check the next quadrant
	if (quad->quads[0] != NULL){
		for (int i = 0; i < 4; i++) {
			//Check if items in next quadrants need to be checked
			if (InBounds({hitbox.x - MAX_COLLISION_DIST_X, hitbox.y - MAX_COLLISION_DIST_Y, 
						  hitbox.x + hitbox.w + MAX_COLLISION_DIST_X, hitbox.y + hitbox.h + MAX_COLLISION_DIST_Y }, quad->quads[i]->dimensions)) {
				BoxCollisionDetector(reference, quad->quads[i], deltaTime);
			}
		}
	}
}

//Detect collision based on hitbox center
void ObjectTree::CircleCollisionDetector(GameObject* reference, float deltaTime) {
	if (head != NULL) {
		CircleCollisionDetector(reference, head, deltaTime);
	}
}
//Determine if a projectile is currently colliding with a wall
void ObjectTree::CircleCollisionDetector(GameObject* reference, ObjectTreeNode* quad, float deltaTime) {
	SDL_Rect item_hitbox;
	SDL_Rect hitbox = { reference->collider->hitbox.x + (reference->collider->hitbox.w / 2), reference->collider->hitbox.y + (reference->collider->hitbox.h / 2), 
						reference->collider->hitbox.w / 2, reference->collider->hitbox.h / 2 };
	int item_centerX, item_centerY, half_width, half_height;

	for (unsigned i = 0; i < quad->items.size(); i++) {
		item_hitbox = quad->items[i]->collider->hitbox;
		half_width = item_hitbox.w / 2;
		half_height = item_hitbox.h / 2;
		item_centerX = item_hitbox.x + half_width;
		item_centerY = item_hitbox.y + half_height;

		//Check distance between centers (squared)
		float distance = pow(hitbox.x - item_centerX, 2) + pow(hitbox.y - item_centerY, 2);
		float distance_total = pow(hitbox.w + half_width, 2);

		if (distance < distance_total){
			reference->collider->CollisionHandler(quad->items[i], 0, 0);
		}
	}

	//Check the next quadrant
	if (quad->quads[0] != NULL) {
		for (int i = 0; i < 4; i++) {
			if (InBounds({hitbox.x - hitbox.w - MAX_COLLISION_DIST_X, hitbox.y - hitbox.h - MAX_COLLISION_DIST_Y, 
						  hitbox.x + hitbox.w + MAX_COLLISION_DIST_X, hitbox.y + hitbox.h + MAX_COLLISION_DIST_Y}, quad->quads[i]->dimensions)) {
				CircleCollisionDetector(reference, quad->quads[i], deltaTime);
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