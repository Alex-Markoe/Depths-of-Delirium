//GUARD
#ifndef __GAMEOBJECT_H_INCLUDED__
#define __GAMEOBJECT_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"

//GAMEOBJECT CLASS
//CONTAINER CLASS WITH INTERCHANGEABLE COMPONENTS
//HOOK UP DIFFERENT COMPONENTS TO CREATE DIFFERENT
//ENTITIES
class GameObject{
public:
	GameObject();
	~GameObject();
	void Update(float deltaTime); //update method, checks all components
	void Init(SDL_Rect _position, bool _dynamic); //set default variables

	bool dynamic; //whether or not an object needs its physics updated
	SDL_Rect position; //global position

	//COMPONENTS
	RenderComponent* renderer;
	AnimationComponent* animator;
	PhysicsComponent* physics;
	CollisionComponent* collider;
	std::vector<Component*> components;
};

#endif //__GAMEOBJECT_H_INCLUDED__