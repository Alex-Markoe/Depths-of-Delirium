#include "ObjectTree.h"

//Constructor
ObjectTree::ObjectTree(int levelWidth, int levelHeight){
	head = new ObjectTreeNode(SDL_Rect{0, 0, levelWidth, levelHeight});
}

ObjectTree::~ObjectTree(){
	delete head;
}

//Public version of the add method
void ObjectTree::Add(GameObject* item){
	Add(item, head);
	count++;
}

//Private version of the add method that uses
//recursion to find the next best quad
void ObjectTree::Add(GameObject* item, ObjectTreeNode* quad){
	if (quad->quads[0] == NULL){
		quad->items.push_back(item);
		int size = quad->items.size();
		if (size > MAX_OBJECTS){
			quad->Divide();
		}
	}
	else{
		if (item->position.x >= quad->quads[0]->dimensions.x && item->position.x + item->sourceRect.w <= quad->quads[0]->dimensions.w + quad->quads[0]->dimensions.x &&
			item->position.y >= quad->quads[0]->dimensions.y && item->position.y + item->sourceRect.h <= quad->quads[0]->dimensions.h + quad->quads[0]->dimensions.y){
			Add(item, quad->quads[0]);
		}
		else if (item->position.x >= quad->quads[1]->dimensions.x && item->position.x + item->sourceRect.w <= quad->quads[1]->dimensions.w + quad->quads[1]->dimensions.x &&
				 item->position.y >= quad->quads[1]->dimensions.y && item->position.y + item->sourceRect.h <= quad->quads[1]->dimensions.h + quad->quads[1]->dimensions.y){
			Add(item, quad->quads[1]);
		}
		else if (item->position.x >= quad->quads[2]->dimensions.x && item->position.x + item->sourceRect.w <= quad->quads[2]->dimensions.w + quad->quads[2]->dimensions.x &&
				 item->position.y >= quad->quads[2]->dimensions.y && item->position.y + item->sourceRect.h <= quad->quads[2]->dimensions.h + quad->quads[2]->dimensions.y){
			Add(item, quad->quads[2]);
		}
		else if (item->position.x >= quad->quads[3]->dimensions.x && item->position.x + item->sourceRect.w <= quad->quads[3]->dimensions.w + quad->quads[3]->dimensions.x &&
				 item->position.y >= quad->quads[3]->dimensions.y && item->position.y + item->sourceRect.h <= quad->quads[3]->dimensions.h + quad->quads[3]->dimensions.y){
			Add(item, quad->quads[3]);
		}
		else{
			quad->items.push_back(item);
		}
	}
}

//Remove all nodes from the tree
void ObjectTree::Reset(int levelWidth, int levelHeight){
	Reset(head);
	head = new ObjectTreeNode(SDL_Rect{0, 0, levelWidth, levelHeight});
	count = 0;
}

//Remove all nodes
void ObjectTree::Reset(ObjectTreeNode* quad){
	if (quad->quads[0] != NULL){
		Reset(quad->quads[0]);
		Reset(quad->quads[1]);
		Reset(quad->quads[2]);
		Reset(quad->quads[3]);
	}
	delete quad;
}

//Detect collision based on box collider
void ObjectTree::BoxCollisionDetector(GameObject &reference) {
	//Bounds of possible collision quadrants
	int collX = reference.hitbox.x - MAX_COLLISION_DIST_X;
	int collY = reference.hitbox.y - MAX_COLLISION_DIST_Y;
	int collW = reference.hitbox.w + reference.hitbox.x + MAX_COLLISION_DIST_X;
	int collH = reference.hitbox.h + reference.hitbox.y + MAX_COLLISION_DIST_Y;

	//reference hitbox
	int x = reference.hitbox.x;
	int y = reference.hitbox.y;
	int width = reference.hitbox.x + reference.hitbox.w;
	int height = reference.hitbox.y + reference.hitbox.h;

	//reference type

	if (head != NULL)
		BoxCollisionDetector(reference, head, SDL_Rect{ collX, collY, collW, collH }, SDL_Rect{ x, y, width, height });
}

//determine if the referenced object is colliding with any objects in its relevant quads
void ObjectTree::BoxCollisionDetector(GameObject &reference, ObjectTreeNode* quad, SDL_Rect coll, SDL_Rect hitboxPosition){
	//Loop through each object in the quad
	//coll = frame of collision detection for quads
	for (unsigned i = 0; i < quad->items.size(); i++) {

		//Check the x direction
		if ((hitboxPosition.y < quad->items[i]->hitbox.y && hitboxPosition.h > quad->items[i]->hitbox.y)
			|| (hitboxPosition.y < quad->items[i]->hitbox.y + quad->items[i]->hitbox.h && hitboxPosition.h > quad->items[i]->hitbox.y + quad->items[i]->hitbox.h)) {
			int speedX = reference.velocity.x + reference.acceleration.x;
			int depthXLeft = hitboxPosition.x - (quad->items[i]->hitbox.w + quad->items[i]->hitbox.x) + speedX;
			int depthXRight = hitboxPosition.w - quad->items[i]->hitbox.x + speedX;
			if (depthXLeft <= 0 && depthXLeft > -MAX_DEPTH_X) //left
				CollisionHandler(reference, quad->items[i], true, depthXLeft);
			else if (depthXRight >= 0 && depthXRight < MAX_DEPTH_X) //right
				CollisionHandler(reference, quad->items[i], true, depthXRight);
		}

		//Check the y direction
		if ((hitboxPosition.x > quad->items[i]->hitbox.x && hitboxPosition.x < quad->items[i]->hitbox.x + quad->items[i]->hitbox.w)
			|| (hitboxPosition.w < quad->items[i]->hitbox.x + quad->items[i]->hitbox.w && hitboxPosition.w > quad->items[i]->hitbox.x)) {
			int speedY = reference.velocity.y + reference.acceleration.y;
			int depthYTop = hitboxPosition.y - (quad->items[i]->hitbox.h + quad->items[i]->hitbox.y) + speedY;
			int depthYBottom = hitboxPosition.h - quad->items[i]->hitbox.y + speedY;
			if (depthYBottom >= 0 && depthYBottom < MAX_DEPTH_Y) //descending
				CollisionHandler(reference, quad->items[i], false, depthYBottom);
			else if (depthYTop <= 0 && depthYTop > -MAX_DEPTH_Y) //ascending
				CollisionHandler(reference, quad->items[i], false, depthYTop);
		}
	}

	//Check the next quadrant
	if (quad->quads[0] != NULL){
		if (InBounds(coll, quad->quads[0])) {
			BoxCollisionDetector(reference, quad->quads[0], coll, hitboxPosition);
		}
		if (InBounds(coll, quad->quads[1])) {
			BoxCollisionDetector(reference, quad->quads[1], coll, hitboxPosition);
		}
		if (InBounds(coll, quad->quads[2])) {
			BoxCollisionDetector(reference, quad->quads[2], coll, hitboxPosition);
		}
		if (InBounds(coll, quad->quads[3])) {
			BoxCollisionDetector(reference, quad->quads[3], coll, hitboxPosition);
		}
	}
}

//Detect collision based on hitbox center
void ObjectTree::CircleCollisionDetector(GameObject &reference) {
	int centerX = reference.hitbox.x + (reference.hitbox.w/2);
	int centerY = reference.hitbox.y + (reference.hitbox.h/2);

	int collX = reference.hitbox.x - MAX_COLLISION_DIST_X;
	int collY = reference.hitbox.y - MAX_COLLISION_DIST_Y;
	int collW = reference.hitbox.x + MAX_COLLISION_DIST_X;
	int collH = reference.hitbox.y + MAX_COLLISION_DIST_Y;

	if (head != NULL)
		CircleCollisionDetector(reference, head, SDL_Rect{ collX, collY, collW, collH }, SDL_Point{centerX, centerY});
}

//Determine if a projectile is currently colliding with a wall
void ObjectTree::CircleCollisionDetector(GameObject &reference, ObjectTreeNode* quad, SDL_Rect coll, SDL_Point center) {
	for (unsigned i = 0; i < quad->items.size(); i++) {

		//Check the x direction
		if (center.y > quad->items[i]->hitbox.y && center.y < quad->items[i]->hitbox.y + quad->items[i]->hitbox.h){
			int speedX = reference.velocity.x + reference.acceleration.x;
			int depthXLeft = center.x - (quad->items[i]->hitbox.w + quad->items[i]->hitbox.x) + speedX;
			int depthXRight = center.x - quad->items[i]->hitbox.x + speedX;
			if (depthXLeft <= 0 && depthXLeft > -MAX_DEPTH_X) //left
				CollisionHandler(reference, quad->items[i], true, depthXLeft);
			else if (depthXRight >= 0 && depthXRight < MAX_DEPTH_X) //right
				CollisionHandler(reference, quad->items[i], true, depthXRight);
		}

		//Check the y direction
		if (center.x > quad->items[i]->hitbox.x && center.x < quad->items[i]->hitbox.x + quad->items[i]->hitbox.w){
			int speedY = reference.velocity.y + reference.acceleration.y;
			int depthYTop = center.y - (quad->items[i]->hitbox.h + quad->items[i]->hitbox.y) + speedY;
			int depthYBottom = center.y - quad->items[i]->hitbox.y + speedY;
			if (depthYBottom >= 0 && depthYBottom < MAX_DEPTH_Y) //descending
				CollisionHandler(reference, quad->items[i], false, depthYBottom);
			else if (depthYTop <= 0 && depthYTop > -MAX_DEPTH_Y) //ascending
				CollisionHandler(reference, quad->items[i], false, depthYTop);
		}
	}

	//Check the next quadrant
	if (quad->quads[0] != NULL) {
		if (InBounds(coll, quad->quads[0])) {
			CircleCollisionDetector(reference, quad->quads[0], coll, center);
		}
		if (InBounds(coll, quad->quads[1])) {
			CircleCollisionDetector(reference, quad->quads[1], coll, center);
		}
		if (InBounds(coll, quad->quads[2])) {
			CircleCollisionDetector(reference, quad->quads[2], coll, center);
		}
		if (InBounds(coll, quad->quads[3])) {
			CircleCollisionDetector(reference, quad->quads[3], coll, center);
		}
	}
}

//public version of the render method
void ObjectTree::Render(SDL_Renderer* renderer){
	if (head != NULL)
		Render(renderer, head);
}

//loop through all the objects in the tree and call their respective render
//methods
void ObjectTree::Render(SDL_Renderer* renderer, ObjectTreeNode* quad) {
	if (quad->items.size() > 0)
		for (unsigned i = 0; i < quad->items.size(); i++){
			quad->items[i]->Draw(renderer);
		}

	if (quad->quads[0] != NULL){
		Render(renderer, quad->quads[0]);
		Render(renderer, quad->quads[1]);
		Render(renderer, quad->quads[2]);
		Render(renderer, quad->quads[3]);
	}
}

//public version of position update method
void ObjectTree::Update(){
	if (head != NULL){
		Update(head);
	}
}

//loop through the tree and call all the Update position methods
//for each object | specialized for moving/swinging platforms
void ObjectTree::Update(ObjectTreeNode* quad){
	if (quad->items.size() > 0){
		for (unsigned i = 0; i <quad->items.size(); i++){
			quad->items[i]->Update();
		}
	}

	if (quad->quads[0] != NULL){
		Update(quad->quads[0]);
		Update(quad->quads[1]);
		Update(quad->quads[2]);
		Update(quad->quads[3]);
	}
}

//Helper function
//Check if an object is within relevant bounds of an adjacent quadrant
bool ObjectTree::InBounds(SDL_Rect coll, ObjectTreeNode* node) {
	return ((coll.x >= node->dimensions.x && coll.x <= node->dimensions.x + node->dimensions.w)
		   || (coll.w >= node->dimensions.x && coll.w <= node->dimensions.x + node->dimensions.w)) &&
		   ((coll.y >= node->dimensions.y && coll.y <= node->dimensions.y + node->dimensions.h)
		   || (coll.h >= node->dimensions.y && coll.h <= node->dimensions.y + node->dimensions.h));
}


//Handle collisions based on the object
void ObjectTree::CollisionHandler(GameObject& reference, GameObject* item, bool dimension, int depth) {
	Tile * t = (Tile*)item;
	std::string name = typeid(reference).name();
	if (name == "class Player") {
		int force = 0;
		switch (t->type) {
			case BOUNCE:
				force = BOUNCE_VELOCITY * (depth / abs(depth));
				break;
			default:
				force = -depth;
				break;
		}

		if (dimension) //x dimension
			reference.ApplyForce(SDL_Point{ force, 0 });
		else //y dimension
			reference.ApplyForce(SDL_Point{ 0, force });
	}
	else if (name == "class Projectile") {
		Projectile* proj = (Projectile*)&reference;
		proj->active = false;
	}
}