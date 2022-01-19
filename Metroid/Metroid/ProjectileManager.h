//GUARD
#ifndef __PROJECTILEMANAGER_H_INCLUDED__
#define __PROJECTILEMANAGER_H_INCLUDED__

//FORWARD DEPENDENCIES
class ObjectTree;
class GameObject;
class Handler;
class ProjectileBehavior;
class ParticleSystemParams;

//INCLUDE DEPENDENCIES
#include <SDL.h>
#include <SDL_image.h>
#include <vector>

//ENUM TO REPRESENT THE TYPE OF
//COLLISION HANDLER FOR THE PROJECTILE
enum HANDLER_TYPE {
	PLAYER_PROJ
};

//PROJECTILE MANAGER SINGLETON
//UPDATES AND ADDS PROJECTILES
//MAKES SURE TO UPDATE THEIR QUADRANT AS WELL AS
//RENDERING THEM
class ProjectileManager {
public:
	static ProjectileManager& instance() {
		static ProjectileManager* instance = new ProjectileManager();
		return *instance;
	};
	~ProjectileManager();
	void Update(float deltaTime, ObjectTree* collision_space);
	void Add(SDL_Rect pos, SDL_Rect source_rect, ProjectileBehavior* behavior, ParticleSystemParams* params, HANDLER_TYPE type, int lifeTime, int max_speed, float decell);
	void Render(SDL_Renderer* gRenderer);

private:
	ProjectileManager();
	std::vector<GameObject*> projectiles; //Container for projectiles
	Handler* handlers; //Array of collision handlers
};

#endif //__PROJECTILEMANAGER_H_INCLUDED__