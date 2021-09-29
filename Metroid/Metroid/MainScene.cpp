#include "MainScene.h"

//Constructor
MainScene::MainScene() {
	collision_space = new ObjectTree(0, 0);
	transitioner = new Transitioner();

	//player = new Player(SDL_Rect{ 0,0,75,78 }, SDL_Rect{ 0, 0, 75, 78 }, SDL_Point{ 12, 3 });

	//CREATE COLLISION HANDLERS
	PoO_handler = new PlayerOnObstacleHandler();

	//INITIALIZE PLATFORMS
	platforms = new GameObject[200];
}
//Destructor
MainScene::~MainScene() {
	delete collision_space;
	delete PoO_handler;
	delete transitioner;
	delete[] platforms;
}

void MainScene::Update() {

}

void MainScene::Render(SDL_Renderer* gRenderer) {
	for (unsigned i = 0; i < active_tile_count; i++) {
		platforms[i].renderer->Render(gRenderer, platforms[i].position);
	}
}

//Initialize the level, and reset from the last level
void MainScene::LoadLevel() {
	std::ifstream fileRead(transitioner->room_file_name, std::ios::in | std::ios::binary | std::ios::beg);

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
			_renderer = new RenderComponent(textures[transitioner->setting], SDL_Rect{ sourceX, sourceY, TILE_SIZE / 2, TILE_SIZE / 2 }, 0.0f);
			_collider = new CollisionComponent(&platforms[total_tile_count], platforms[total_tile_count].position, SDL_Point{ 0, 0 }, OBSTACLE);
			_collider->PlayerCollision = PoO_handler;
			platforms[total_tile_count].renderer = _renderer;
			platforms[total_tile_count].collider = _collider;

			collision_space->Add(&platforms[total_tile_count]);
			total_tile_count++;
			active_tile_count++;
		}

		//CLEANUP
		delete[] lvl_Data;
		fileRead.close();
	}
}