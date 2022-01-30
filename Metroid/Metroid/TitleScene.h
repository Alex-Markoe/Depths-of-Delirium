//GUARD
#ifndef __TITLESCENE_H_INCLUDED__
#define __TITLESCENE_H_INCLUDED__

//FORWARD DEPENDENCIES
class ContinueGameCommand;
class ToNewGameCommand;
class ExitGameCommand;
class GameObject;

//INCLUDE DEPENDENCIES
#include "Scene.h"

//TITLE SCENE
//IT IS LITERALLY JUST BUTTONS 
class TitleScene : public Scene{
public:
	TitleScene();
	~TitleScene();
	void Update(float deltaTime) override;
	void Render(SDL_Renderer* gRenderer) override;

private:
	GameObject* buttons;
	ToNewGameCommand* new_game_cmd;
	ContinueGameCommand* cont_game_cmd;
	ExitGameCommand* exit_cmd;

	const int BUTTON_SIZE_X = 300; //CHANGE TO MAKE BUTTONS DIFFERENT SIZES!!!
	const int BUTTON_SIZE_Y = 150;
};

#endif //__TITLESCENE_H_INCLUDED__