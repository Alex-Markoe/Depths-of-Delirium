#include "GameObject.h"

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
		delete components[i];
	}
	components.clear();
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
}