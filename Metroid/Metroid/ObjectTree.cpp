#include "ObjectTree.h"

ObjectTree::ObjectTree(int levelWidth, int levelHeight){
	head = new ObjectTreeNode(SDL_Rect{0, 0, levelWidth, levelHeight});
}

ObjectTree::~ObjectTree(){

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


std::vector<GameObject*> ObjectTree::CollisionDetector(GameObject &reference){
	ObjectTreeNode* current = head;
	std::vector<GameObject*> collisionItems;

	int x = reference.hitbox.x - MAX_COLLISION_DIST_X;
	int y = reference.hitbox.y - MAX_COLLISION_DIST_Y;
	int width = reference.hitbox.w + reference.hitbox.x + MAX_COLLISION_DIST_X;
	int height = reference.hitbox.h + reference.hitbox.y + MAX_COLLISION_DIST_Y;

	while (current != NULL){

		if (current->items.size() > 0){
			for (std::vector<GameObject*>::iterator it = current->items.begin(); it != current->items.end(); ++it) {
				GameObject* item = *it;
				if (item->position.x >= x && item->position.x + item->sourceRect.w <= width &&
					item->position.y >= y && item->position.y + item->sourceRect.h <= height) {
					collisionItems.push_back(item);
				}
			}
		}

		if (current->quads[0] != NULL){
			if (((x >= current->quads[0]->dimensions.x && x <= current->quads[0]->dimensions.x + current->quads[0]->dimensions.w) 
				|| (width >= current->quads[0]->dimensions.x && width <= current->quads[0]->dimensions.x + current->quads[0]->dimensions.w)) &&
				((y >= current->quads[0]->dimensions.y && y <= current->quads[0]->dimensions.y + current->quads[0]->dimensions.h)
				|| (height >= current->quads[0]->dimensions.y && height <= current->quads[0]->dimensions.y + current->quads[0]->dimensions.h))) {
				current = head->quads[0];
			}
			if (((x >= current->quads[1]->dimensions.x && x <= current->quads[1]->dimensions.x + current->quads[1]->dimensions.w)
				|| (width >= current->quads[1]->dimensions.x && width <= current->quads[1]->dimensions.x + current->quads[1]->dimensions.w)) &&
				((y >= current->quads[1]->dimensions.y && y <= current->quads[1]->dimensions.y + current->quads[1]->dimensions.h)
					|| (height >= current->quads[1]->dimensions.y && height <= current->quads[1]->dimensions.y + current->quads[1]->dimensions.h))) {
				current = head->quads[1];
			}
			if (((x >= current->quads[2]->dimensions.x && x <= current->quads[2]->dimensions.x + current->quads[2]->dimensions.w)
				|| (width >= current->quads[2]->dimensions.x && width <= current->quads[2]->dimensions.x + current->quads[2]->dimensions.w)) &&
				((y >= current->quads[2]->dimensions.y && y <= current->quads[2]->dimensions.y + current->quads[2]->dimensions.h)
					|| (height >= current->quads[2]->dimensions.y && height <= current->quads[2]->dimensions.y + current->quads[2]->dimensions.h))) {
				current = head->quads[2];
			}
			if (((x >= current->quads[3]->dimensions.x && x <= current->quads[3]->dimensions.x + current->quads[3]->dimensions.w)
				|| (width >= current->quads[3]->dimensions.x && width <= current->quads[3]->dimensions.x + current->quads[3]->dimensions.w)) &&
				((y >= current->quads[3]->dimensions.y && y <= current->quads[3]->dimensions.y + current->quads[3]->dimensions.h)
					|| (height >= current->quads[3]->dimensions.y && height <= current->quads[3]->dimensions.y + current->quads[3]->dimensions.h))) {
				current = head->quads[3];
			}
		}
		else{
			current = NULL;
		}
	}

	return collisionItems;
}