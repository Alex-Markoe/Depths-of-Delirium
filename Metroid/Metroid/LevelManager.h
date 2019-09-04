#pragma once
#include "Player.h"
#include "ObjectTree.h"
#include <iostream>
#include <fstream>

class LevelManager{
public:
	LevelManager();
	~LevelManager();
	void LoadLevel();
	void ClearLevel();
	void Init();
	void PlatformCollision(Player player);

private:
	std::ofstream fileRead;
};

