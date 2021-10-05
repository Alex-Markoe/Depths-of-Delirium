#include "PauseScene.h"
#include "ToTitleCommand.h"
#include "UnpauseCommand.h"

//Constructor
PauseScene::PauseScene() {
	to_title_cmd = new ToTitleCommand();
	unpause_cmd = new UnpauseCommand();

	buttons = new GameObject[2]; 
	RenderComponent* _renderer = nullptr;
	CollisionComponent* _collider = nullptr;
	int off_y = 450;
	for (unsigned i = 0; i < 2; i++) {
		buttons[i].position = SDL_Rect{ 300, 100 + (off_y), BUTTON_SIZE_X, BUTTON_SIZE_Y };
		_renderer = new RenderComponent(TextureDatabase::instance().GetTexture(BUTTON_TXT), SDL_Rect{ 0, 0 + off_y, BUTTON_SIZE_X, BUTTON_SIZE_Y }, 0);
		_collider = new CollisionComponent(&buttons[i], buttons[i].position, SDL_Point{ 0, 0 }, OBSTACLE);
		buttons[i].renderer = _renderer;
		buttons[i].collider = _collider;

		off_y += BUTTON_SIZE_Y;
		_renderer = nullptr;
		_collider = nullptr;
	}
	buttons[0].components.emplace_back(new ButtonComponent(buttons[0].collider, to_title_cmd)); //RETURN TO TITLE BUTTON
	buttons[1].components.emplace_back(new ButtonComponent(buttons[1].collider, unpause_cmd)); //RETURN TO GAME BUTTON
}
//Destructor
PauseScene::~PauseScene() {
	delete[] buttons;
	delete to_title_cmd;
	delete unpause_cmd;
}

void PauseScene::Update(float deltaTime) {
	for (unsigned i = 0; i < 2; i++) {
		buttons[i].Update(deltaTime);
	}
}

void PauseScene::Render(SDL_Renderer* gRenderer) {
	for (unsigned i = 0; i < 2; i++) {
		buttons[i].renderer->Render(gRenderer, buttons[i].position);
	}
}