#include "TitleScene.h"
#include "ToNewGameCommand.h"
#include "ContinueGameCommand.h"
#include "ExitGameCommand.h"

//Constructor
TitleScene::TitleScene() {
	new_game_cmd = new ToNewGameCommand();
	cont_game_cmd = new ContinueGameCommand();
	exit_cmd = new ExitGameCommand();

	buttons = new GameObject[3];
	RenderComponent* _renderer = nullptr;
	CollisionComponent* _collider = nullptr;
	int off_y = 0;
	for (unsigned i = 0; i < 3; i++) {
		buttons[i].Init(SDL_Rect{ 300, 100 + (off_y + 100), BUTTON_SIZE_X, BUTTON_SIZE_Y }, false);
		_renderer = new RenderComponent(TextureDatabase::instance().GetTexture(BUTTON_TXT), SDL_Rect{ 0, 0 + off_y, BUTTON_SIZE_X, BUTTON_SIZE_Y }, 0);
		_collider = new CollisionComponent(&buttons[i], buttons[i].position, SDL_Point{ 0, 0 }, OBSTACLE);
		buttons[i].renderer = _renderer;
		buttons[i].collider = _collider;

		off_y += BUTTON_SIZE_Y;
		_renderer = nullptr;
		_collider = nullptr;
	}
	buttons[0].components.emplace_back(new ButtonComponent(buttons[0].collider, new_game_cmd)); //NEW GAME BUTTON
	buttons[1].components.emplace_back(new ButtonComponent(buttons[1].collider, cont_game_cmd)); //CONTINUE GAME BUTTON
	buttons[2].components.emplace_back(new ButtonComponent(buttons[2].collider, exit_cmd)); //EXIT GAME BUTTON
}
//Destructor
TitleScene::~TitleScene() {
	delete[] buttons;
	delete new_game_cmd;
	delete cont_game_cmd;
	delete exit_cmd;
}

void TitleScene::Update(float deltaTime) {
	for (unsigned i = 0; i < 3; i++) {
		buttons[i].Update(deltaTime);
	}
}

void TitleScene::Render(SDL_Renderer* gRenderer) {
	for (unsigned i = 0; i < 3; i++) {
		buttons[i].renderer->Render(gRenderer, buttons[i].position);
	}
}