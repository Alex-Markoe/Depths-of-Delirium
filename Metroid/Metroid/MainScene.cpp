#include "MainScene.h"
#include "FileManager.h"
#include "SceneManager.h"
#include "ObjectTree.h"
#include "GameObject.h"
#include "TextureDatabase.h"

//COLLISION HANDLERS
#include "PlayerCollisionHandler.h"
#include "TransitionCollisionHandler.h"

//COMPONENTS
#include "RenderComponent.h"
#include "PhysicsComponent.h"
#include "AnimationComponent.h"
#include "CollisionComponent.h"
#include "PlayerComponent.h"
#include "BossComponent.h"

#include <fstream>

//FOR TEST
#include "ParticleSystemComponent.h" //remove later
#include "ParticleSystemParams.h" //remove later
#include "IceWheelProjectileBehavior.h"
//REMOVE LATER

//Constructor
MainScene::MainScene() {
	//INITIALIZE PLATFORMS
	platforms = new GameObject[200];
	collidables = new GameObject[20];
	key_state = SDL_GetKeyboardState(NULL);

	//CREATE COLLISION HANDLERS
	player_collision_handler = new PlayerCollisionHandler();
	to_next_handler = new TransitionCollisionHandler(this, true);
	to_previous_handler = new TransitionCollisionHandler(this, false);

	//CREATE MANAGERS
	collision_space = new ObjectTree(32 * TILE_SIZE, 18 * TILE_SIZE);

	//player = new Player(SDL_Rect{ 0,0,75,78 }, SDL_Rect{ 0, 0, 75, 78 }, SDL_Point{ 12, 3 });
	//INITIALIZE PLAYER
	player = new GameObject();
	player->Init({ 0, 0, 135, 144 }, true);
	player->renderer = new RenderComponent(TextureDatabase::instance().GetTexture(PLAYER_TXT), { 0, 0, 135, 144 }, 0);
	player->collider = new CollisionComponent(player, player->position, { 20, 33 }, PLAYER, player_collision_handler);
	player->physics = new PhysicsComponent({ 40, 40 }, 0.8f, 1.0f);
	player->animator = new AnimationComponent(player->renderer);
	player->AddComponent(new PlayerComponent(player->renderer, player->physics, player->animator, player->collider, player));
	ProjectileManager::instance().GetPlayer(player);

	//INITIALIZE BOSS
	boss = new GameObject();
	boss->Init({ 0, 0, 0, 0 }, true);
	boss->renderer = new RenderComponent(nullptr, { 0, 0, 0, 0 }, 0);
	boss->collider = new CollisionComponent(boss, boss->position, { 0, 0 }, BOSS, nullptr);
	boss->physics = new PhysicsComponent({ 0, 0 }, 1.0f, 1.0f);
	boss->animator = new AnimationComponent(boss->renderer);
	boss->AddComponent(new BossComponent());

	//particles_test = new GameObject();
	//particles_test->Init({ 300, 300, 0, 0 }, false);
	//ParticleSystemParams p(0, 10, 300, 150, 10, 0, 360, false, false, 0.7f, 150, 10.0f, { 0, 0 }, { 50, 50 }, FIRE_PARTICLE, STRAIGHT_ACCELERATING);
	//particles_test->AddComponent(new ParticleSystemComponent(p, particles_test));
}
//Destructor
MainScene::~MainScene() {
	delete player;
	delete boss;
	delete collision_space;
	delete player_collision_handler;
	delete to_next_handler;
	delete to_previous_handler;
	delete[] platforms;
	delete[] collidables;

	//delete particles_test;
}
//Update all objects in the level
void MainScene::Update(float deltaTime) {
	//CHECK IF THE GAME SHOULD BE PAUSED
	if (key_state[SDL_SCANCODE_ESCAPE]) {
		SceneManager::instance().ChangeScene(PAUSE);
	}

	//Check collision, and check if player is outside 
	//of their quadrant
	player->Update(deltaTime);
	if (player->collider->out_of_quad) {
		player->collider->ResetQuad();
		collision_space->Add(player);
	}
	collision_space->BoxCollisionDetector(player, deltaTime);
	ProjectileManager::instance().Update(deltaTime, collision_space);
	//particles_test->Update(deltaTime);
}
//Render all objects in the level
void MainScene::Render(SDL_Renderer* gRenderer) {
	for (unsigned i = 0; i < active_tile_count; i++) {
		platforms[i].Render(gRenderer);
	}
	player->Render(gRenderer);
	ProjectileManager::instance().Render(gRenderer);
	//particles_test->Render(gRenderer);
}

//Initialize the level, and reset from the last level
void MainScene::LoadLevel() {
	if (FileManager::instance().ReadFile()) {
		//INITIALIZE BOSS DATA
	}
	//GET THE PLAYER ENTRY POSITION AND UPDATE THEIR 
	//POSITION
	SDL_Point ppos = FileManager::instance().enter_position;
	player->position = SDL_Rect{ppos.x, ppos.y, player->position.w, player->position.h};
	player->physics->ResetKinematics(true, true);
	player->physics->ApplyForce(0, 500);
	player->collider->UpdatePosition(player->position);
	std::ifstream file_read(FileManager::instance().room_file_name, std::ios::in | std::ios::beg);
	ProjectileManager::instance().Clear();

	//FOR TEST ===
	IceWheelProjectileBehavior* behavior = new IceWheelProjectileBehavior();
	behavior->SetForce(-200, 0);
	ProjectileManager::instance().Add({ 300, 300, 63, 63 }, { 0, 0, 63, 63 }, { 5, 5 }, behavior, nullptr, ICE_WHEEL, ICE_PROJECTILE_TXT, 10000, 20, 1.0f);
	//FOR TEST ===

	if (file_read.is_open()) {
		//CLEAR OUT PREVIOUS DATA
		collision_space->Clear();
		total_tile_count = 0;
		active_tile_count = 0;
		total_colliders_count = 0;
		active_colliders_count = 0;

		//GET THE LEVEL BASED TILE TEXTURES
		SDL_Texture* txt = TextureDatabase::instance().GetTexture(FileManager::instance().setting);
		int x = 0, i_x = 0, y = 0, width, height, sourceX, sourceY;
		std::string data = "";
		std::string plat_data[6];
		size_t pos = 0;

		//Loop through the entire level and add the tiles
		while (std::getline(file_read, data)) {
			//ADD THE PLATFORM DATA TO THE ARRAY
			for (int i = 0; i < 6; i++) {
				pos = data.find(',');
				plat_data[i] = data.substr(0, pos);
				data.erase(0, pos + 1);
			}
			//PLATFORM DETAILS
			//X
			x = std::stoi(plat_data[0]);
			//Y
			y = std::stoi(plat_data[1]);
			//WIDTH
			width = std::stoi(plat_data[2]);
			//HEIGHT
			height = std::stoi(plat_data[3]);
			//CREATE COLLIDER
			//CREATE NEW COMPONENT, OR ADJUST IF IT ALREADY EXISTS
			collidables[total_colliders_count].Init({ x * TILE_SIZE, y * TILE_SIZE, width * TILE_SIZE, height * TILE_SIZE }, false);
			if (collidables[total_colliders_count].collider == nullptr) 
				collidables[total_colliders_count].collider = new CollisionComponent(&collidables[total_colliders_count], collidables[total_colliders_count].position, {0, 0}, OBSTACLE, nullptr);
			else collidables[total_colliders_count].collider->SetHitbox({ x * TILE_SIZE, y * TILE_SIZE, width * TILE_SIZE, height * TILE_SIZE }, {0, 0});
			if (plat_data[5] == "T") { //IF THE PLATFORM IS TO BE LOADED IN NOW, ADD IT, OTHERWISE MARK IT
				collision_space->Add(&collidables[total_colliders_count]);
				active_colliders_count++;
			}
			total_colliders_count++;

			if (plat_data[4][0] == 'L') {
				collidables[total_colliders_count - 1].collider->SetHandler(to_next_handler);
				continue;
			}
			if (plat_data[4][0] == 'Z') {
				collidables[total_colliders_count - 1].collider->SetHandler(to_previous_handler);
				continue;
			}
			i_x = x;
			//READ VISUALS
			for (unsigned i = 0; i < plat_data[4].size(); i++) {
				//TOP PLATFORM
				if (plat_data[4][i] == 'F') {
					sourceX = 0;
					sourceY = 0;
				}
				//TOP RIGHT PLATFORM
				else if (plat_data[4][i] == 'O') {
					sourceX = 60;
					sourceY = 0;
				}
				//TOP LEFT PLATFORM
				else if (plat_data[4][i] == 'W') {
					sourceX = 30;
					sourceY = 0;
				}
				//CENTER PLATFORM
				else if (plat_data[4][i] == 'G') {
					sourceX = 60;
					sourceY = 60;
				}
				//BOTTOM PLATFORM
				else if (plat_data[4][i] == 'P') {
					sourceX = 30;
					sourceY = 60;
				}
				//LEFT PLATFORM
				else if (plat_data[4][i] == 'T') {
					sourceX = 60;
					sourceY = 30;
				}
				//RIGHT PLATFORM
				else if (plat_data[4][i] == 'Y') {
					sourceX = 30;
					sourceY = 30;
				}
				//PLATFORM
				else if (plat_data[4][i] == 'Q') {
					sourceX = 0;
					sourceY = 90;
				}
				//LEFT CORNER PLATFORM
				else if (plat_data[4][i] == 'A') {
					sourceX = 30;
					sourceY = 90;
				}
				//RIGHT CORNER PLATFORM
				else if (plat_data[4][i] == 'K') {
					sourceX = 60;
					sourceY = 90;
				}
				//SLOW PLATFORM
				else if (plat_data[4][i] == 'S') {
					sourceX = 0;
					sourceY = 0;
				}

				//UPDATE PLATFORMS
				//CREATE NEW COMPONENT IF NEEDED, UPDATE IF NOT
				platforms[total_tile_count].Init({ x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE }, false);
				if (platforms[total_tile_count].renderer == nullptr) platforms[total_tile_count].renderer = new RenderComponent(txt, { sourceX, sourceY, TILE_SIZE / 2, TILE_SIZE / 2 }, 0.0f);
				else platforms[total_tile_count].renderer->Init(txt, { sourceX, sourceY, TILE_SIZE / 2, TILE_SIZE / 2 }, 0.0f);
				total_tile_count++;
				if (plat_data[5] == "T") active_tile_count++; //SAME AS BEFORE, DISPLAY IF MARKED PROPERLY

				x++;
				if (x >= width) {
					x = i_x;
					y++;
				}
			}
		}

		collision_space->Add(player);
		file_read.close();
	}
}