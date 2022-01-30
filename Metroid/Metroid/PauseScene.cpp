#include "PauseScene.h"
#include "GameObject.h"
#include "TextureDatabase.h"

//COMMANDS
#include "ToTitleCommand.h"
#include "UnpauseCommand.h"

//COMPONENTS
#include "ButtonComponent.h"
#include "RenderComponent.h"
#include "CollisionComponent.h"

//Constructor
PauseScene::PauseScene() {
	//INITIALIZE COMMANDS
	to_title_cmd = new ToTitleCommand();
	unpause_cmd = new UnpauseCommand();

	//CREATE THE BUTTONS
	buttons = new GameObject[2]; 
	int off_y = 450;
	for (unsigned i = 0; i < 2; i++) {
		buttons[i].Init(SDL_Rect{ 300, 100 + (off_y), BUTTON_SIZE_X, BUTTON_SIZE_Y }, false);
		buttons[i].renderer = new RenderComponent(TextureDatabase::instance().GetTexture(BUTTON_TXT), SDL_Rect{ 0, 0 + off_y, BUTTON_SIZE_X, BUTTON_SIZE_Y }, 0);
		buttons[i].collider = new CollisionComponent(&buttons[i], buttons[i].position, SDL_Point{ 0, 0 }, OBSTACLE);

		off_y += BUTTON_SIZE_Y;
	}
	buttons[0].AddComponent(new ButtonComponent(buttons[0].collider, to_title_cmd)); //RETURN TO TITLE BUTTON
	buttons[1].AddComponent(new ButtonComponent(buttons[1].collider, unpause_cmd)); //RETURN TO GAME BUTTON
}
//Destructor
PauseScene::~PauseScene() {
	delete[] buttons;
	delete to_title_cmd;
	delete unpause_cmd;
}
//UPDATE BUTTONS
void PauseScene::Update(float deltaTime) {
	for (unsigned i = 0; i < 2; i++) {
		buttons[i].Update(deltaTime);
	}
}
//RENDER BUTTONS
void PauseScene::Render(SDL_Renderer* gRenderer) {
	for (unsigned i = 0; i < 2; i++) {
		buttons[i].renderer->Render(gRenderer, buttons[i].position);
	}
}