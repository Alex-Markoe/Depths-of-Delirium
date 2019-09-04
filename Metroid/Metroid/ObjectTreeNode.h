#pragma once
#include "GameObject.h"
#include <SDL.h>
#include <vector>
#include <iostream>

class ObjectTreeNode{
public:
	ObjectTreeNode(SDL_Rect dim);
	~ObjectTreeNode();
	void Divide();

	std::vector<GameObject*> items;
	ObjectTreeNode *quads[4];
	SDL_Rect dimensions;

private:
	const int MAX_OBJECTS = 5;
};