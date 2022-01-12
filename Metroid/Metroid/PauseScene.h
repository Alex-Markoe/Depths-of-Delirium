//GUARD
#ifndef __PAUSESCENE_H_INCLUDED__
#define __PAUSESCENE_H_INCLUDED__

//FORWARD DEPENDENCIES
class ToTitleCommand;
class UnpauseCommand;

//INCLUDE DEPENDENCIES
#include "Scene.h"

class PauseScene : public Scene {
public:
	PauseScene();
	~PauseScene();
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* gRenderer) override;

private:
	GameObject* buttons;
	ToTitleCommand* to_title_cmd;
	UnpauseCommand* unpause_cmd;

	const int BUTTON_SIZE_X = 300;
	const int BUTTON_SIZE_Y = 150;
};

#endif //__PAUSESCENE_H_INCLUDED__