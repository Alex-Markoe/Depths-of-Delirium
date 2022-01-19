#include "MainScene.h"
#include "FileManager.h"
#include "SceneManager.h"
#include "ObjectTree.h"

//COLLISION HANDLERS
#include "PlayerCollisionHandler.h"

//COMPONENTS
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"
#include "PlayerComponent.h"
#include "ParticleSystemComponent.h" //remove later
#include "ParticleSystemParams.h" //remove later

#include <fstream>

//Constructor
MainScene::MainScene() {
	//INITIALIZE PLATFORMS
	platforms = new GameObject[200];
	key_state = SDL_GetKeyboardState(NULL);

	//CREATE COLLISION HANDLERS
	player_collision_handler = new PlayerCollisionHandler();

	//CREATE MANAGERS
	collision_space = new ObjectTree(32 * TILE_SIZE, 18 * TILE_SIZE);

	//player = new Player(SDL_Rect{ 0,0,75,78 }, SDL_Rect{ 0, 0, 75, 78 }, SDL_Point{ 12, 3 });
	//INITIALIZE PLAYER
	player = new GameObject();
	player->Init(SDL_Rect{ 0, 0, 75, 78 }, true);
	player->renderer = new RenderComponent(TextureDatabase::instance().GetTexture(PLAYER_TXT), SDL_Rect{ 0, 0, 75, 78 }, 0);
	player->collider = new CollisionComponent(player, player->position, SDL_Point{ 12, 3 }, PLAYER);
	player->physics = new PhysicsComponent(SDL_Point{ 40, 40 }, 0.8f, 1.0f);
	player->animator = new AnimationComponent(player->renderer);
	player->AddComponent(new PlayerComponent(player->renderer, player->physics, player->animator, player));
	player->collider->SetHandler(player_collision_handler);

	particles_test = new GameObject();
	particles_test->Init({ 300, 300, 0, 0 }, false);
	ParticleSystemParams p(0, 10, 300, 100, 2, 0, 360, false, false, 0.7f, 150, 0.0f, { 0, 0 }, { 0, 0 }, FIRE_PARTICLE, STRAIGHT_ACCELERATING);
	particles_test->AddComponent(new ParticleSystemComponent(p, particles_test));
}
//Destructor
MainScene::~MainScene() {
	delete player;
	delete collision_space;
	delete player_collision_handler;
	delete[] platforms;

	delete particles_test;
}
//Update all objects in the level
void MainScene::Update(float deltaTime) {
	//PAUSE
	if (key_state[SDL_SCANCODE_ESCAPE]) {
		SceneManager::instance().ChangeScene(PAUSE);
	}

	//Check collision, and check if player is outside 
	//of their quadrant
	collision_space->BoxCollisionDetector(player, deltaTime);
	player->Update(deltaTime);
	if (player->collider->out_of_quad) {
		player->collider->ResetQuad();
		collision_space->Add(player);
	}
	ProjectileManager::instance().Update(deltaTime, collision_space);
	particles_test->Update(deltaTime);
}
//Render all objects in the level
void MainScene::Render(SDL_Renderer* gRenderer) {
	for (unsigned i = 0; i < active_tile_count; i++) {
		platforms[i].Render(gRenderer);
	}
	player->Render(gRenderer);
	ProjectileManager::instance().Render(gRenderer);
	particles_test->Render(gRenderer);
}

//Initialize the level, and reset from the last level
void MainScene::LoadLevel() {
	if (FileManager::instance().ReadFile()) {
		//INITIALIZE BOSS DATA
	}
	SDL_Point ppos = FileManager::instance().enter_position;
	player->position = SDL_Rect{ppos.x, ppos.y, player->position.w, player->position.h};
	player->physics->ResetKinematics();
	player->physics->ApplyForce(0, 500);
	player->collider->UpdatePosition(player->position);
	std::ifstream fileRead(FileManager::instance().room_file_name, std::ios::in | std::ios::binary | std::ios::beg);

	if (fileRead.is_open()) {
		//Reset all data structs and read in the level dimensions
		fileRead.read(reinterpret_cast<char*>(&LEVEL_HEIGHT), sizeof(LEVEL_HEIGHT));
		fileRead.read(reinterpret_cast<char*>(&LEVEL_WIDTH), sizeof(LEVEL_WIDTH));
		collision_space->Clear();
		//if (platforms != NULL) delete[] platforms;
		total_tile_count = 0;
		active_tile_count = 0;

		//Read in all the level information
		std::streampos lvl_Begin, lvl_End;
		lvl_Begin = fileRead.tellg();
		fileRead.seekg(0, std::ios::end);
		lvl_End = fileRead.tellg();
		fileRead.seekg(lvl_Begin);
		int size = lvl_End - lvl_Begin;
		char * lvl_Data = new char[size];
		fileRead.read(lvl_Data, size);

		//GameObject* tile = nullptr;
		RenderComponent* _renderer = nullptr;
		CollisionComponent* _collider = nullptr;
		SDL_Texture* txt = TextureDatabase::instance().GetTexture(FileManager::instance().setting);
		int x = -1, y = 0, sourceX, sourceY;
		//Loop through the entire level and add the tiles
		for (unsigned i = 0; i < size; i++) {
			x++;
			if (x >= LEVEL_WIDTH) {
				x = 0;
				y++;
			}

			//BACKGROUND
			if (lvl_Data[i] == 'B') {
				continue;
			}

			//TOP PLATFORM
			else if (lvl_Data[i] == 'F') {
				sourceX = 0;
				sourceY = 0;
			}
			//TOP RIGHT PLATFORM
			else if (lvl_Data[i] == 'O') {
				sourceX = 60;
				sourceY = 0;
			}
			//TOP LEFT PLATFORM
			else if (lvl_Data[i] == 'W') {
				sourceX = 30;
				sourceY = 0;
			}
			//CENTER PLATFORM
			else if (lvl_Data[i] == 'G') {
				sourceX = 60;
				sourceY = 60;
			}
			//BOTTOM PLATFORM
			else if (lvl_Data[i] == 'P') {
				sourceX = 30;
				sourceY = 60;
			}
			//LEFT PLATFORM
			else if (lvl_Data[i] == 'T') {
				sourceX = 60;
				sourceY = 30;
			}
			//RIGHT PLATFORM
			else if (lvl_Data[i] == 'Y') {
				sourceX = 30;
				sourceY = 30;
			}
			//PLATFORM
			else if (lvl_Data[i] == 'Q') {
				sourceX = 0;
				sourceY = 90;
			}
			//LEFT CORNER PLATFORM
			else if (lvl_Data[i] == 'A') {
				sourceX = 30;
				sourceY = 90;
			}
			//RIGHT CORNER PLATFORM
			else if (lvl_Data[i] == 'K') {
				sourceX = 60;
				sourceY = 90;
			}
			//TRANSITION TILE
			else if (lvl_Data[i] == 'L') {
				sourceX = -1;
				sourceY = -1;
			}
			//SLOW PLATFORM
			else if (lvl_Data[i] == 'S') {
				sourceX = 0;
				sourceY = 0;
			}

			_renderer = nullptr;
			_collider = nullptr;

			//CREATE TILE AND ADD ITS COMPONENTS
			platforms[total_tile_count].Init(SDL_Rect{ x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE }, false);
			_renderer = new RenderComponent(txt, SDL_Rect{ sourceX, sourceY, TILE_SIZE / 2, TILE_SIZE / 2 }, 0.0f);
			_collider = new CollisionComponent(&platforms[total_tile_count], platforms[total_tile_count].position, SDL_Point{ 0, 0 }, OBSTACLE);
			platforms[total_tile_count].renderer = _renderer;
			platforms[total_tile_count].collider = _collider;

			collision_space->Add(&platforms[total_tile_count]);
			total_tile_count++;
			active_tile_count++;
		}
		collision_space->Add(player);
		//CLEANUP
		delete[] lvl_Data;
		fileRead.close();
	}
}