#include "ObjectTreeNode.h"
#include "GameObject.h"
#include "CollisionComponent.h"

//Constructor
//Create dimensions and initalize items
ObjectTreeNode::ObjectTreeNode(SDL_Rect dim){
	dimensions = dim;
	items = std::vector<GameObject*>();
}
//Destructor
//recursively delete children
ObjectTreeNode::~ObjectTreeNode(){
	if (quads[0] != NULL) {
		delete quads[0];
		delete quads[1];
		delete quads[2];
		delete quads[3];
	}
}
//Divide the quad, and create new
//child quads and set their parent
void ObjectTreeNode::Divide(){
	quads[0] = new ObjectTreeNode(SDL_Rect{dimensions.x, dimensions.y, dimensions.w/2, dimensions.h/2});
	quads[1] = new ObjectTreeNode(SDL_Rect{dimensions.x + (dimensions.w/2), dimensions.y, dimensions.w/2, dimensions.h/2});
	quads[2] = new ObjectTreeNode(SDL_Rect{dimensions.x, dimensions.y + (dimensions.h/2), dimensions.w/2, dimensions.h/2});
	quads[3] = new ObjectTreeNode(SDL_Rect{dimensions.x + (dimensions.w/2), dimensions.y + (dimensions.h/2), dimensions.w/2, dimensions.h/2});
}
//Get rid of an object at a particular index
//and update the indicies of the objects after it
void ObjectTreeNode::Erase(int index) {
	items.erase(items.begin() + index);
	while (index < items.size()) {
		items[index]->collider->item_index--;
		index++;
	}
}
//Add object to the array of items
//and setup the object's collider
void ObjectTreeNode::Add(GameObject* item) {
	item->collider->SetQuad(items.size(), this);
	items.push_back(item);
}