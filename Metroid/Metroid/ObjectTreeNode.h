//GUARD
#ifndef __OBJECTTREENODE_H_INCLUDED__
#define __OBJECTTREENODE_H_INCLUDED__

//FORWARD DEPENDENICES
class GameObject;

//INCLUDE DEPENDENCIES
#include <SDL.h>
#include <vector>

//BASE TREE NODE 
//HOLDS DATA ABOUT QUAD DIMENSIONS
//CHILDREN, CONTAINED OBJECTS, AND THE PARENT
class ObjectTreeNode{
public:
	ObjectTreeNode(SDL_Rect dim);
	~ObjectTreeNode();
	void Divide();
	void Erase(int index);

	std::vector<GameObject*> items;
	ObjectTreeNode* quads[4];
	SDL_Rect dimensions;
};

#endif //__OBJECTTREENODE_H_INCLUDED__