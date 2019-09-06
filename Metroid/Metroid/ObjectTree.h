#pragma once
#include "ObjectTreeNode.h"
#include <string>
#include <fstream>
#include <vector>

class ObjectTree{
public:
	ObjectTree(int levelWidth, int levelHeight);
	~ObjectTree();
	void Add(GameObject* item);
	std::vector<GameObject*> AllObjects();
	std::vector<GameObject*> CollisionDetector(GameObject &reference);
	void Reset(int levelWidth, int levelHeight);

private:
	ObjectTreeNode* head;

	const int MAX_OBJECTS = 5;
	const int MAX_COLLISION_DIST_X = 30;
	const int MAX_COLLISION_DIST_Y = 30;

	void Add(GameObject* item, ObjectTreeNode* quad);
	void Reset(ObjectTreeNode* quad);
	std::vector<GameObject*> AllObjects(ObjectTreeNode* quad);
};

