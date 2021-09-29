//GUARD
#ifndef __OBJECTTREE_H_INCLUDED__
#define __OBJECTTREE_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "ObjectTreeNode.h"

//HELPER FUNCTION FORWARD DEFINITIONS
bool InBounds(SDL_Rect in_rect, SDL_Rect encapsulating_rect);
bool InQuad(SDL_Rect hitbox, SDL_Rect quad);

//SPATIAL PARTITIONING TREE THAT DIVIDES
//THE SCREEN INTO DIFFERENT QUADRANTS
//DETERMINES IF TWO OBJECTS HAVE COLLIDED
class ObjectTree{
public:
	ObjectTree(int levelWidth, int levelHeight);
	~ObjectTree();
	void Add(GameObject* item);
	void BoxCollisionDetector(GameObject* reference);
	void CircleCollisionDetector(GameObject* reference);
	void Reset(int levelWidth, int levelHeight);
	void Clear();

private:
	ObjectTreeNode* head;

	const int MAX_COLLISION_DIST_X = 15;
	const int MAX_COLLISION_DIST_Y = 15;
	const int MAX_DEPTH_X = 30;
	const int MAX_DEPTH_Y = 30;

	void Init(int levelWidth, int levelHeight);
	void Divide(int iterations, ObjectTreeNode* quad);
	void Add(GameObject* item, ObjectTreeNode* quad);
	void BoxCollisionDetector(GameObject* reference, ObjectTreeNode* quad, SDL_Rect collisionSpace, SDL_Rect hitbox);
	void CircleCollisionDetector(GameObject* reference, ObjectTreeNode* quad, SDL_Rect collisionSpace, SDL_Rect hitbox);
	void Clear(ObjectTreeNode* quad);
};

#endif //__OBJECTTREE_H_INCLUDED__