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
	void CollisionDetector(GameObject &reference);
	void Reset(int levelWidth, int levelHeight);
	void Render(SDL_Renderer* renderer);

	std::vector<GameObject*> AllObjects();
	int count;

private:
	ObjectTreeNode* head;

	const int MAX_OBJECTS = 5;
	const int MAX_COLLISION_DIST_X = 30;
	const int MAX_COLLISION_DIST_Y = 30;
	const int MAX_DEPTH_X = 16;
	const int MAX_DEPTH_Y = 20;
	const int BOUNCE_VELOCITY = 10;

	void Add(GameObject* item, ObjectTreeNode* quad);
	void Reset(ObjectTreeNode* quad);
	void Render(SDL_Renderer* renderer, ObjectTreeNode* quad);
	std::vector<GameObject*> AllObjects(ObjectTreeNode* quad);
};

