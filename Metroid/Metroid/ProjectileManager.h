//GUARD
#ifndef __PROJECTILEMANAGER_H_INCLUDED__
#define __PROJECTILEMANAGER_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "GameObject.h"
#include <vector>

class ProjectileManager
{
public:
	static ProjectileManager& instance() {
		static ProjectileManager* instance = new ProjectileManager();
		return *instance;
	};
	~ProjectileManager();
	virtual void Update();
	void Remove(GameObject* toRemove);
	virtual void Add(SDL_Rect pos, SDL_Point force, bool playerOwned, float angle);
	void Render();
	std::vector<GameObject*> projectiles;

private:
	ProjectileManager(){};
};

#endif //__PROJECTILEMANAGER_H_INCLUDED__