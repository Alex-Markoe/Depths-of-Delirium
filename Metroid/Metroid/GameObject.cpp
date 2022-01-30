#include "GameObject.h"
#include "AnimationComponent.h"
#include "PhysicsComponent.h"
#include "CollisionComponent.h"
#include "RenderComponent.h"

//Constructor
GameObject::GameObject(){
	physics = nullptr;
	renderer = nullptr;
	collider = nullptr;
	animator = nullptr;
}
//Destructor
GameObject::~GameObject(){
	if (physics != nullptr) delete physics;
	if (renderer != nullptr) delete renderer;
	if (collider != nullptr) delete collider;
	if (animator != nullptr) delete animator;
	for (int i = 0; i < components.size(); i++) {
		if (components[i] != nullptr) delete components[i];
	}
	components.clear();
	/*for (int i = 0; i < children.size(); i++) {
		if (children[i] != nullptr) delete children[i];
	}*/
	children.clear();
}

//Set initial variables
void GameObject::Init(SDL_Rect _position, bool _dynamic) {
	position = _position;
	dynamic = _dynamic;
}

//Update all components
void GameObject::Update(float deltaTime){
	//Check physics
	if (dynamic) {
		if (physics != nullptr) {
			physics->UpdatePosition(position, deltaTime);
			if (collider != nullptr) collider->UpdatePosition(position);
		}
	}
	//Check attachable components
	for (unsigned i = 0; i < components.size(); i++) components[i]->Update();
	if (animator != nullptr) animator->Update();
	//Update children
	for (int i = 0; i < children.size(); i++) {
		children[i]->Update(deltaTime);
	}
}

//Render the object
void GameObject::Render(SDL_Renderer* gRenderer) {
	if (renderer != nullptr) renderer->Render(gRenderer, position);
	for (int i = 0; i < children.size(); i++) {
		children[i]->Render(gRenderer);
	}
}
//Add a new component to the object
void GameObject::AddComponent(Component* component) {
	components.emplace_back(component);
}
//Add a child object to be rendered
void GameObject::AddChild(GameObject* obj) {
	children.push_back(obj);
}