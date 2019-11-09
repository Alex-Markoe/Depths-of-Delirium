#pragma once
#include "ObjectTreeNode.h"
#include "Player.h"
#include "Tile.h"
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
	void UpdatePosition();

	std::vector<GameObject*> AllObjects();
	int count;

private:
	ObjectTreeNode* head;

	const int MAX_OBJECTS = 5;
	const int MAX_COLLISION_DIST_X = 30;
	const int MAX_COLLISION_DIST_Y = 30;
	const int MAX_DEPTH_X = 20;
	const int MAX_DEPTH_Y = 30;
	const int BOUNCE_VELOCITY = 10;

	void Add(GameObject* item, ObjectTreeNode* quad);
	void Reset(ObjectTreeNode* quad);
	void Render(SDL_Renderer* renderer, ObjectTreeNode* quad);
	void UpdatePosition(ObjectTreeNode* quad);
	void CollisionDetector(GameObject &reference, ObjectTreeNode* quad, SDL_Rect coll, SDL_Rect pHPos);
	void CollisionHandler(GameObject& reference, GameObject* item, bool dimension, int depth);
	std::vector<GameObject*> AllObjects(ObjectTreeNode* quad);
};

