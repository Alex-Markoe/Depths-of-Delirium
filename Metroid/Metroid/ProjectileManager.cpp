#include "ProjectileManager.h"
#include "TextureDatabase.h"
#include "ObjectTree.h"
#include "GameObject.h"
#include "ParticleSystemParams.h"

//COMPONENTS
#include "ProjectileComponent.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "ParticleSystemComponent.h"

//COLLISION HANDLERS
#include "PlayerProjectileCollisionHandler.h"
#include "ReboundCollisionHandler.h"
#include "IceWheelCollisionHandler.h"

//Constructor
//Initialize collision handlers
ProjectileManager::ProjectileManager() {
	handlers.push_back(new PlayerProjectileCollisionHandler());
	handlers.push_back(new ReboundCollisionHandler());
	handlers.push_back(new IceWheelCollisionHandler());
}
//Destructor, remove any remaining projectiles
//as well as getting rid of collision handlers
ProjectileManager::~ProjectileManager(){
	while (projectiles.size() > 0){
		delete projectiles.front();
		projectiles.erase(projectiles.begin());
	}
	while (handlers.size() > 0) {
		delete handlers.front();
		handlers.erase(handlers.begin());
	}
}

//Update all projectiles contained in the manager
void ProjectileManager::Update(float deltaTime, ObjectTree* collision_space) {
	for (unsigned i = 0; i < projectiles.size(); i++){
		projectiles[i]->Update(deltaTime);

		//Check if the projectile is no
		//longer active
		ProjectileComponent* p = (ProjectileComponent*)projectiles[i]->components[0];
		if (p->dead) {
			delete projectiles[i];
			projectiles.erase(projectiles.begin() + i);
			i--;
		}
		else if (p->active) {
			//Check if the projectile has moved out of its
			//quadrant, and update if needed
			if (projectiles[i]->collider->out_of_quad) {
				projectiles[i]->collider->ResetQuad();
				collision_space->Add(projectiles[i]);
			}
			collision_space->BoxCollisionDetector(projectiles[i], deltaTime);
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
void ProjectileManager::Add(SDL_Rect pos, SDL_Rect source_rect, SDL_Point hitbox_offset, ProjectileBehavior* behavior, 
							ParticleSystemParams* params, HANDLER_TYPE type, int txt, int lifeTime, int max_speed, float decell){
	GameObject* proj = new GameObject();
	proj->Init(pos, true);
	proj->renderer = new RenderComponent(TextureDatabase::instance().GetTexture(txt), source_rect, 0);
	proj->collider = new CollisionComponent(proj, proj->position, hitbox_offset, PROJECTILE);
	proj->physics = new PhysicsComponent({ max_speed, max_speed }, decell, decell);
	proj->animator = new AnimationComponent(proj->renderer);
	ParticleSystemComponent* particles = nullptr;
	if (params != nullptr) particles = new ParticleSystemComponent(*params, proj);
	proj->AddComponent(new ProjectileComponent(lifeTime, proj->physics, proj->collider, proj->renderer, proj->animator, particles, behavior));
	if (particles != nullptr) proj->AddComponent(particles);
	proj->collider->out_of_quad = true;
	proj->collider->SetHandler(handlers[type]);
	projectiles.emplace_back(proj);
}
void ProjectileManager::GetPlayer(GameObject* player) {
	ReboundCollisionHandler* r = (ReboundCollisionHandler*)handlers[1];
	r->SetPlayer(player);
}