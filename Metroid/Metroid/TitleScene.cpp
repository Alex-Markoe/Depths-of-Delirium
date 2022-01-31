#include "TitleScene.h"
#include "GameObject.h"
#include "TextureDatabase.h"

//COMMANDS
#include "ToNewGameCommand.h"
#include "ContinueGameCommand.h"
#include "ExitGameCommand.h"

//COMPONENTS
#include "ButtonComponent.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"

//Constructor
TitleScene::TitleScene() {
	//INITIALIZE COMMANDS
	new_game_cmd = new ToNewGameCommand();
	cont_game_cmd = new ContinueGameCommand();
	exit_cmd = new ExitGameCommand();

	//INITIALIZE THE BUTTONS
	buttons = new GameObject[3];
	int off_y = 0;
	for (unsigned i = 0; i < 3; i++) {
		buttons[i].Init(SDL_Rect{ 600, 100 + (off_y + 100), BUTTON_SIZE_X, BUTTON_SIZE_Y }, false);
		buttons[i].renderer = new RenderComponent(TextureDatabase::instance().GetTexture(BUTTON_TXT), SDL_Rect{ 0, 0 + off_y, BUTTON_SIZE_X, BUTTON_SIZE_Y }, 0);;
		buttons[i].collider = new CollisionComponent(&buttons[i], buttons[i].position, SDL_Point{ 0, 0 }, OBSTACLE, nullptr);

		off_y += BUTTON_SIZE_Y;
	}
	buttons[0].AddComponent(new ButtonComponent(buttons[0].collider, new_game_cmd)); //NEW GAME BUTTON
	buttons[1].AddComponent(new ButtonComponent(buttons[1].collider, cont_game_cmd)); //CONTINUE GAME BUTTON
	buttons[2].AddComponent(new ButtonComponent(buttons[2].collider, exit_cmd)); //EXIT GAME BUTTON
}
//Destructor
TitleScene::~TitleScene() {
	delete[] buttons;
	delete new_game_cmd;
	delete cont_game_cmd;
	delete exit_cmd;
}
//UPDATE THE BUTTONS
void TitleScene::Update(float deltaTime) {
	for (unsigned i = 0; i < 3; i++) {
		buttons[i].Update(deltaTime);
	}
}
//RENDER THE BUTTONS
void TitleScene::Render(SDL_Renderer* gRenderer) {
	for (unsigned i = 0; i < 3; i++) {
		buttons[i].renderer->Render(gRenderer, buttons[i].position);
	}
}