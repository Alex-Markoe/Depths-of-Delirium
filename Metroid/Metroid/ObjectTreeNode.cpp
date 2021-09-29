#include "ObjectTreeNode.h"
//Constructor
ObjectTreeNode::ObjectTreeNode(SDL_Rect dim){
	dimensions = dim;
	items = std::vector<GameObject*>();
}
//Destructor
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
	for (int i = 0; i < 4; i++) {
		quads[i]->parent = this;
	}
}