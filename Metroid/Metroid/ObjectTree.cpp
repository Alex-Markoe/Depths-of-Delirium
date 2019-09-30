#include "ObjectTree.h"
#include "Tile.h"

ObjectTree::ObjectTree(int levelWidth, int levelHeight){
	head = new ObjectTreeNode(SDL_Rect{0, 0, levelWidth, levelHeight});
}

ObjectTree::~ObjectTree(){

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
		if (item->position.x >= quad->quads[1]->dimensions.x && item->position.x + item->sourceRect.w <= quad->quads[1]->dimensions.w + quad->quads[1]->dimensions.x &&
			item->position.y >= quad->quads[1]->dimensions.y && item->position.y + item->sourceRect.h <= quad->quads[1]->dimensions.h + quad->quads[1]->dimensions.y){
			Add(item, quad->quads[1]);
		}
		if (item->position.x >= quad->quads[2]->dimensions.x && item->position.x + item->sourceRect.w <= quad->quads[2]->dimensions.w + quad->quads[2]->dimensions.x &&
			item->position.y >= quad->quads[2]->dimensions.y && item->position.y + item->sourceRect.h <= quad->quads[2]->dimensions.h + quad->quads[2]->dimensions.y){
			Add(item, quad->quads[2]);
		}
		if (item->position.x >= quad->quads[3]->dimensions.x && item->position.x + item->sourceRect.w <= quad->quads[3]->dimensions.w + quad->quads[3]->dimensions.x &&
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
	delete head;
	head = new ObjectTreeNode(SDL_Rect{0, 0, levelWidth, levelHeight});
	count = 0;
}

void ObjectTree::Reset(ObjectTreeNode* quad){
	if (quad->quads[0] != NULL){
		Reset(quad->quads[0]);
		Reset(quad->quads[1]);
		Reset(quad->quads[2]);
		Reset(quad->quads[3]);
	}
	delete quad;
}


void ObjectTree::CollisionDetector(GameObject &reference){
	ObjectTreeNode* current = head;

	int collX = reference.hitbox.x - MAX_COLLISION_DIST_X;
	int collY = reference.hitbox.y - MAX_COLLISION_DIST_Y;
	int collW = reference.hitbox.w + reference.hitbox.x + MAX_COLLISION_DIST_X;
	int collH = reference.hitbox.h + reference.hitbox.y + MAX_COLLISION_DIST_Y;

	int x = reference.hitbox.x;
	int y = reference.hitbox.y;
	int width = reference.hitbox.x + reference.hitbox.w;
	int height = reference.hitbox.y + reference.hitbox.h;
	int centerX = (reference.hitbox.w / 2) + reference.hitbox.x;
	int centerY = (reference.hitbox.h / 2) + reference.hitbox.y;

	while (current != NULL){

		if (current->items.size() > 0){
			for (unsigned i = 0; i < current->items.size(); i++) {

				int depthX = centerX - ((current->items[i]->hitbox.w / 2) + current->items[i]->hitbox.x) + reference.velocity.x;
				int depthY = centerY - ((current->items[i]->hitbox.h / 2) + current->items[i]->hitbox.y) + reference.velocity.y;
				
				//Check the x direction
				if (depthX <= 0 && depthX > -MAX_DEPTH_X
					&& ((y > current->items[i]->hitbox.y && y < current->items[i]->hitbox.y + current->items[i]->hitbox.h)
						|| (height > current->items[i]->hitbox.y && height < current->items[i]->hitbox.y + current->items[i]->hitbox.h))) {
					Tile * t = (Tile*)current->items[i];
					switch (t->type) {
					case Bounce:
						reference.velocity.x = BOUNCE_VELOCITY;
						break;
					default:
						reference.velocity.x += depthX;
						break;
					}
				}
				else if (depthX >= 0 && depthX < MAX_DEPTH_X
					&& ((y > current->items[i]->hitbox.y && y < current->items[i]->hitbox.y + current->items[i]->hitbox.h)
						|| (height > current->items[i]->hitbox.y && height < current->items[i]->hitbox.y + current->items[i]->hitbox.h))) {
					Tile * t = (Tile*)current->items[i];
					switch (t->type) {
					case Bounce:
						reference.velocity.x = -BOUNCE_VELOCITY;
						break;
					default:
						reference.velocity.x -= depthX;
						break;
					}
				}

				//Check the y direction
				if (depthY <= 0 && depthY > -MAX_DEPTH_Y
					&& ((x > current->items[i]->hitbox.x && x < current->items[i]->hitbox.x + current->items[i]->hitbox.w)
						|| (width > current->items[i]->hitbox.x && width < current->items[i]->hitbox.x + current->items[i]->hitbox.w))) {
					Tile * t = (Tile*)current->items[i];
					switch (t->type) {
					case Bounce:
						reference.velocity.y = BOUNCE_VELOCITY;
						break;
					default:
						reference.velocity.y += depthY;
						break;
					}
				}
				else if (depthY >= 0 && depthY < MAX_DEPTH_Y
					&& ((x > current->items[i]->hitbox.x && x < current->items[i]->hitbox.x + current->items[i]->hitbox.w)
						|| (width > current->items[i]->hitbox.x && width < current->items[i]->hitbox.x + current->items[i]->hitbox.w))) {
					Tile * t = (Tile*)current->items[i];
					switch (t->type) {
					case Bounce:
						reference.velocity.y = -BOUNCE_VELOCITY;
						break;
					default:
						reference.velocity.y += depthY;
						break;
					}
				}
			}
		}

		if (current->quads[0] != NULL){
			if (((collX >= current->quads[0]->dimensions.x && collX <= current->quads[0]->dimensions.x + current->quads[0]->dimensions.w) 
				|| (collW >= current->quads[0]->dimensions.x && collW <= current->quads[0]->dimensions.x + current->quads[0]->dimensions.w)) &&
				((collY >= current->quads[0]->dimensions.y && collY <= current->quads[0]->dimensions.y + current->quads[0]->dimensions.h)
				|| (collY >= current->quads[0]->dimensions.y && collY <= current->quads[0]->dimensions.y + current->quads[0]->dimensions.h))) {
				current = head->quads[0];
			}
			if (((collX >= current->quads[1]->dimensions.x && collX <= current->quads[1]->dimensions.x + current->quads[1]->dimensions.w)
				|| (collW >= current->quads[1]->dimensions.x && collW <= current->quads[1]->dimensions.x + current->quads[1]->dimensions.w)) &&
				((collY >= current->quads[1]->dimensions.y && collY <= current->quads[1]->dimensions.y + current->quads[1]->dimensions.h)
				|| (collY >= current->quads[1]->dimensions.y && collY <= current->quads[1]->dimensions.y + current->quads[1]->dimensions.h))) {
				current = head->quads[1];
			}
			if (((collX >= current->quads[2]->dimensions.x && collX <= current->quads[2]->dimensions.x + current->quads[2]->dimensions.w)
				|| (collW >= current->quads[2]->dimensions.x && collW <= current->quads[2]->dimensions.x + current->quads[2]->dimensions.w)) &&
				((collY >= current->quads[2]->dimensions.y && collY <= current->quads[2]->dimensions.y + current->quads[2]->dimensions.h)
					|| (collY >= current->quads[2]->dimensions.y && collY <= current->quads[2]->dimensions.y + current->quads[2]->dimensions.h))) {
				current = head->quads[2];
			}
			if (((collX >= current->quads[3]->dimensions.x && collX <= current->quads[3]->dimensions.x + current->quads[3]->dimensions.w)
				|| (collW >= current->quads[3]->dimensions.x && collW <= current->quads[3]->dimensions.x + current->quads[3]->dimensions.w)) &&
				((collY >= current->quads[3]->dimensions.y && collY <= current->quads[3]->dimensions.y + current->quads[3]->dimensions.h)
				|| (collY >= current->quads[3]->dimensions.y && collY <= current->quads[3]->dimensions.y + current->quads[3]->dimensions.h))) {
				current = head->quads[3];
			}
			else{
				current = NULL;
			}
		}
		else{
			current = NULL;
		}
	}
}

//Methods to return all the objects in the tree
std::vector<GameObject*> ObjectTree::AllObjects(){
	if (head != NULL){
		return AllObjects(head);
	}
	else{
		std::vector<GameObject*> nothing;
		return nothing;
	}
}

std::vector<GameObject*> ObjectTree::AllObjects(ObjectTreeNode* quad){
	std::vector<GameObject*> items = std::vector<GameObject*>();

	for (unsigned i = 0; i < quad->items.size(); i++) {
		items.push_back(quad->items[i]);
	}

	if (quad->quads[0] != NULL){
		std::vector<GameObject*> moreItems = AllObjects(quad->quads[0]);
		if (moreItems.size() > 0)
			for (unsigned i = 0; i < moreItems.size(); i++){
				items.push_back(moreItems[i]);
			}

		moreItems = AllObjects(quad->quads[1]);
		if (moreItems.size() > 0)
			for (unsigned i = 0; i < moreItems.size(); i++) {
				items.push_back(moreItems[i]);
			}

		moreItems = AllObjects(quad->quads[2]);
		if (moreItems.size() > 0)
			for (unsigned i = 0; i < moreItems.size(); i++) {
				items.push_back(moreItems[i]);
			}

		moreItems = AllObjects(quad->quads[3]);
		if (moreItems.size() > 0)
			for (unsigned i = 0; i < moreItems.size(); i++) {
				items.push_back(moreItems[i]);
			}
	}
	
	return items;
}

void ObjectTree::Render(SDL_Renderer* renderer){
	if (head != NULL)
		Render(renderer, head);
}

void ObjectTree::Render(SDL_Renderer* renderer, ObjectTreeNode* quad) {
	if (quad->items.size() > 0)
		for (unsigned i = 0; i < quad->items.size(); i++){
			quad->items[i]->Draw(renderer);
		}

	if (quad->quads[0] != NULL){
		Render(renderer, quad->quads[0]);
		Render(renderer, quad->quads[0]);
		Render(renderer, quad->quads[0]);
		Render(renderer, quad->quads[0]);
	}
}

void ObjectTree::UpdatePosition(){
	if (head != NULL){
		UpdatePosition(head);
	}
}

void ObjectTree::UpdatePosition(ObjectTreeNode* quad){
	if (quad->items.size() > 0){
		for (unsigned i = 0; i <quad->items.size(); i++){
			quad->items[i]->UpdatePosition();
		}
	}

	if (quad->quads[0] != NULL){
		UpdatePosition(quad->quads[0]);
		UpdatePosition(quad->quads[1]);
		UpdatePosition(quad->quads[2]);
		UpdatePosition(quad->quads[3]);
	}
}