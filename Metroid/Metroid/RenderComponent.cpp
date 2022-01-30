#include "RenderComponent.h"

//Constructor
RenderComponent::RenderComponent(SDL_Texture* _texture, SDL_Rect _source_rect, float _angle) {
	Init(_texture, _source_rect, _angle);
	flip_type = SDL_FLIP_NONE;
}
//Destructor
RenderComponent::~RenderComponent() {
	texture = nullptr; //Texture is destroyed later 
}

//Simple function to render the object to the screen
void RenderComponent::Render(SDL_Renderer* gRenderer, SDL_Rect position) {
	SDL_RenderCopyEx(gRenderer, texture, &source_rect, &position, angle, NULL, flip_type);
}
//Setters/Getters
void RenderComponent::SetFlip(SDL_RendererFlip _flip) { flip_type = _flip; }
void RenderComponent::SetAngle(float _angle) { angle = _angle; }
float RenderComponent::GetAngle() { return angle; }
void RenderComponent::Update() {}
void RenderComponent::Init(SDL_Texture* _texture, SDL_Rect _source_rect, float _angle) {
	texture = _texture;
	source_rect = _source_rect;
	angle = _angle;
}