#include "ObjectTreeNode.h"

ObjectTreeNode::ObjectTreeNode(SDL_Rect dim){
	dimensions = dim;
	items = std::vector<GameObject*>();
}

ObjectTreeNode::~ObjectTreeNode(){
	items.clear();
}

void ObjectTreeNode::Divide(){
	quads[0] = new ObjectTreeNode(SDL_Rect{dimensions.x, dimensions.y, dimensions.w/2, dimensions.h/2});
	quads[1] = new ObjectTreeNode(SDL_Rect{ dimensions.x + dimensions.w/2, dimensions.y, dimensions.w / 2, dimensions.h / 2 });
	quads[2] = new ObjectTreeNode(SDL_Rect{ dimensions.x, dimensions.y + dimensions.h/2, dimensions.w / 2, dimensions.h / 2 });
	quads[3] = new ObjectTreeNode(SDL_Rect{ dimensions.x + dimensions.w/2, dimensions.y + dimensions.h/2, dimensions.w / 2, dimensions.h / 2 });
	std::vector<int> toRemove = std::vector<int>();

	for (unsigned i = 0; i < items.size(); ++i){
		
		int X = items[i]->position.x;
		int Y = items[i]->position.y;
		int iWIDTH = X + items[i]->sourceRect.w;
		int iHEIGHT = Y + items[i]->sourceRect.y;

		if (X >= quads[0]->dimensions.x && iWIDTH <= quads[0]->dimensions.w && Y >= quads[0]->dimensions.y && iHEIGHT <= quads[0]->dimensions.h){
			quads[0]->items.push_back(items[i]);
			toRemove.push_back(i);
		}
		else if (X >= quads[1]->dimensions.x && iWIDTH <= quads[1]->dimensions.w && Y >= quads[1]->dimensions.y && iHEIGHT <= quads[1]->dimensions.h) {
			quads[1]->items.push_back(items[i]);
			toRemove.push_back(i);
		}
		else if (X >= quads[2]->dimensions.x && iWIDTH <= quads[2]->dimensions.w && Y >= quads[2]->dimensions.y && iHEIGHT <= quads[2]->dimensions.h) {
			quads[2]->items.push_back(items[i]);
			toRemove.push_back(i);
		}
		else if (X >= quads[3]->dimensions.x && iWIDTH <= quads[3]->dimensions.w && Y >= quads[3]->dimensions.y && iHEIGHT <= quads[3]->dimensions.h) {
			quads[3]->items.push_back(items[i]);
			toRemove.push_back(i);
		}
	}

	for (unsigned i = 0; i < toRemove.size(); i++){
		items.erase(items.begin() + toRemove[i] - 1);
	}
}