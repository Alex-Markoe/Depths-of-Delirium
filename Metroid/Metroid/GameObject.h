//GUARD
#ifndef __GAMEOBJECT_H_INCLUDED__
#define __GAMEOBJECT_H_INCLUDED__

//FORWARD DEPENDENCIES
class AnimationComponent;
class PhysicsComponent;
class CollisionComponent;
class RenderComponent;
class Component;

//INCLUDE DEPENDENCIES
#include <SDL.h>
#include <vector>

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
	void Render(SDL_Renderer* gRenderer);
	void AddComponent(Component* component);
	void AddChild(GameObject* obj);

	SDL_Rect position; //global position

	//COMPONENTS
	RenderComponent* renderer;
	AnimationComponent* animator;
	PhysicsComponent* physics;
	CollisionComponent* collider;
	std::vector<Component*> components;

private:
	std::vector<GameObject*> children;
	bool dynamic; //whether or not an object needs its physics updated
};

#endif //__GAMEOBJECT_H_INCLUDED__