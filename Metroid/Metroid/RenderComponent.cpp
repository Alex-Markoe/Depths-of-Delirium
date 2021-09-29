#include "RenderComponent.h"
//Constructor
RenderComponent::RenderComponent(SDL_Texture* _texture, SDL_Rect _sourceRect, float _angle) {
	texture = _texture;
	sourceRect = _sourceRect;
	angle = _angle;
	flipType = SDL_FLIP_NONE;
}
//Destructor
RenderComponent::~RenderComponent() {
	texture = nullptr;
}

//Simple function to render the object to the screen
void RenderComponent::Render(SDL_Renderer* gRenderer, SDL_Rect position) {
	SDL_RenderCopyEx(gRenderer, texture, &sourceRect, &position, angle, NULL, flipType);
}

void RenderComponent::SetFlip(SDL_RendererFlip _flip) { flipType = _flip; }
void RenderComponent::Update() {}