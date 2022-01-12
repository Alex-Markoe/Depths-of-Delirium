//GUARD
#ifndef __RENDERCOMPONENT_H_INCLUDED__
#define __RENDERCOMPONENT_H_INCLUDED__

//INCLUDE DEPENDENCIES
#include "Component.h"

//ESSENTIAL COMPONENTS
//HANDLES RENDERING OBJECT TEXTURE
class RenderComponent : public Component {
public:
	RenderComponent(SDL_Texture* _texture, SDL_Rect _sourceRect, float _angle);
	~RenderComponent();
	void Update() override;
	void Render(SDL_Renderer* gRenderer, SDL_Rect position);
	void SetFlip(SDL_RendererFlip _flip);
	void SetAngle(float _angle);

	SDL_Rect sourceRect;

private:
	SDL_Texture* texture;
	SDL_RendererFlip flipType;

	float angle;
};

#endif //__RENDERCOMPONENT_H_INCLUDED__