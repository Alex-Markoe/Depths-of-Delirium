#pragma once
#include "ObjectTreeNode.h"
#include "Player.h"
#include "Tile.h"
#include <string>
#include <fstream>
#include <vector>

bool InBounds(SDL_Rect coll, ObjectTreeNode* node);
void CollisionHandler(GameObject& reference, GameObject* item, bool dimension, int depth);

class ObjectTree{
public:
	ObjectTree(int levelWidth, int levelHeight);
	~ObjectTree();
	void Add(GameObject* item);
	void BoxCollisionDetector(GameObject &reference);
	void CircleCollisionDetector(GameObject &reference);
	void Reset(int levelWidth, int levelHeight);
	void Render(SDL_Renderer* renderer);
	void Update();

	int count;

private:
	ObjectTreeNode* head;

	const int MAX_OBJECTS = 5;
	const int MAX_COLLISION_DIST_X = 15;
	const int MAX_COLLISION_DIST_Y = 15;
	const int MAX_DEPTH_X = 30;
	const int MAX_DEPTH_Y = 30;
	const int BOUNCE_VELOCITY = 10;

	void Add(GameObject* item, ObjectTreeNode* quad);
	void Reset(ObjectTreeNode* quad);
	void Render(SDL_Renderer* renderer, ObjectTreeNode* quad);
	void Update(ObjectTreeNode* quad);
	void BoxCollisionDetector(GameObject &reference, ObjectTreeNode* quad, SDL_Rect coll, SDL_Rect futurePosition);
	void CircleCollisionDetector(GameObject &reference, ObjectTreeNode* quad, SDL_Rect coll, SDL_Point center);
};

