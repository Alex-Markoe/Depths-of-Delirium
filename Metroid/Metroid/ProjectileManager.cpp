#include "ProjectileManager.h"
#include "TextureDatabase.h"
#include "ObjectTree.h"
#include "GameObject.h"

//COMPONENTS
#include "ProjectileComponent.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"

//COLLISION HANDLERS
#include "PlayerProjectileCollisionHandler.h"

//Constructor
//Initialize collision handlers
ProjectileManager::ProjectileManager() {
	handlers = new Handler[5];
	handlers[0] = PlayerProjectileCollisionHandler();
}
//Destructor, remove any remaining projectiles
//as well as getting rid of collision handlers
ProjectileManager::~ProjectileManager(){
	while (projectiles.size() > 0){
		delete projectiles.front();
		projectiles.erase(projectiles.begin());
	}
	delete[] handlers;
}

//Update all projectiles contained in the manager
void ProjectileManager::Update(float deltaTime, ObjectTree* collision_space) {
	for (unsigned i = 0; i < projectiles.size(); i++){
		projectiles[i]->Update(deltaTime);

		//Check if the projectile has moved out of its
		//quadrant, and update if needed
		if (projectiles[i]->collider->out_of_quad) {
			projectiles[i]->collider->ResetQuad();
			collision_space->Add(projectiles[i]);
		}
		collision_space->CircleCollisionDetector(projectiles[i], deltaTime);

		//Check if the projectile is no
		//longer active
		ProjectileComponent* p = (ProjectileComponent*)projectiles[i]->components[0];
		if (!p->active) {
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
	}
}

//Render all projectiles in the manager
void ProjectileManager::Render(SDL_Renderer* gRenderer) {
	for (unsigned i = 0; i < projectiles.size(); i++){
		projectiles[i]->Render(gRenderer);
	}
}

//Add a new projectile to the collection
//and initialize their components
void ProjectileManager::Add(SDL_Rect pos, SDL_Rect source_rect, ProjectileBehavior* behavior, HANDLER_TYPE type, int lifeTime){
	GameObject* proj = new GameObject();
	proj->Init(pos, true);
	proj->renderer = new RenderComponent(TextureDatabase::instance().GetTexture(PROJECTILE_TXT), source_rect, 0);
	proj->collider = new CollisionComponent(proj, proj->position, {0, 0}, PROJECTILE);
	proj->physics = new PhysicsComponent({50, 50}, 1.0f, 1.0f);
	proj->animator = new AnimationComponent(proj->renderer);
	proj->AddComponent(new ProjectileComponent(lifeTime, proj->physics, proj->renderer, proj->animator, behavior));
	proj->collider->out_of_quad = true;
	proj->collider->SetHandler(&handlers[type]);
	projectiles.emplace_back(proj);
}