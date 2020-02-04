#include "LevelManager.h"

//Constructor, initialize all important variables
LevelManager::LevelManager(std::map<std::string, std::string> textures, SDL_Renderer* renderer){
	platforms = new ObjectTree(0, 0);
	lvlTransition = new Transitioner();
	projectiles = new ProjectileManager(renderer);

	textureFiles = textures;
	gRenderer = renderer;

	player = new Player(SDL_Rect{ 0,0,75,78 }, SDL_Rect{ 0, 0, 75, 78 }, SDL_Point{ 12, 3 }, projectiles);
	player->loadTexture(textureFiles["PlayerSheet"], gRenderer);

	transitioning = false;
}

//Destructor
LevelManager::~LevelManager(){
	delete player;
	delete lvlTransition;
	delete platforms;
	delete projectiles;
	gRenderer = nullptr;
	transitions.clear();
}

//Call all update methods of any objects in the level
void LevelManager::Update(){
	//Update all the objects in the level
	player->Update();
	projectiles->Update();
	
	//Check collisions
	if (platforms->count != 0){
		platforms->Update();
		platforms->CollisionDetector(*player);
		for (unsigned i = 0; i < projectiles->projectiles.size(); i++) {
			platforms->CollisionDetector(*projectiles->projectiles[i]);
		}
	}

	//Change positions
	player->UpdatePosition();

	//Change the level if a transition is hit
	TransitionCollisions();
	if (transitioning){
		lvlTransition->roomNumber++;
		SDL_Point p = lvlTransition->Update();
		player->position.x = p.x;
		player->position.y = p.y;
		Init();
	}
}

//Render all relevant objects
void LevelManager::RenderAll(){
	if (platforms->count != 0) {
		platforms->Render(gRenderer);
	}
	
	projectiles->Render();
	player->Draw(gRenderer);
}

//Initialize the level, and reset from the last level
void LevelManager::Init(){
	std::ifstream fileRead(lvlTransition->roomName, std::ios::in | std::ios::binary | std::ios::beg);

	if (fileRead.is_open()){
		//Reset all data structs and read in the level dimensions
		fileRead.read(reinterpret_cast<char*>(&levelHeight), sizeof(levelHeight));
		fileRead.read(reinterpret_cast<char*>(&levelWidth), sizeof(levelWidth));
		platforms->Reset(levelWidth * TILE_SIZE, levelHeight * TILE_SIZE);

		//Read in all the level information
		std::streampos lvl_Begin, lvl_End;
		lvl_Begin = fileRead.tellg();
		fileRead.seekg(0, std::ios::end);
		lvl_End = fileRead.tellg();
		fileRead.seekg(lvl_Begin);
		int size = lvl_End - lvl_Begin;
		char * lvl_Data = new char[size];

		//Arrays to hold the tiles needing to be read
		fileRead.read(lvl_Data, size);
		std::string futureTiles = "";
		ReadLevelData(lvl_Data, futureTiles, 0, levelWidth);
		std::string tilesToRead = futureTiles;
		std::string previousTiles = tilesToRead;

		//Enums denoting variables about the tile to be placed
		TILE_TYPE type = BACKGROUND;
		TILE_ORIENTATION orientation = HORIZONTAL_MIDDLE;
		SDL_Point pivotPos = SDL_Point{0,0};

		//Loop through the entire level and add the tiles
		for (unsigned i = 0; i < levelHeight; i++){
			if (i < levelHeight - 1)
				ReadLevelData(lvl_Data, futureTiles, i + 1, levelWidth);

			for (unsigned j = 0; j < levelWidth; j++){
				//Background spaces
				if (tilesToRead[j] == 'B') { 
					type = BACKGROUND;
				}
				
				//Regular platforms
				else if (tilesToRead[j] == 'F') { 
					type = PLATFORM;

					//Check the left and right adjacent tiles 
					if (j == 0) {//Check if its the first tile in the row
						if (tilesToRead[j + 1] == 'B')
							orientation = HORIZONTAL_RIGHT;
						else
							orientation = HORIZONTAL_MIDDLE;
					}
					else if (j == levelWidth - 1) {//Check if its the last tile in the row
						if (tilesToRead[j - 1] == 'B')
							orientation = HORIZONTAL_LEFT;
						else
							orientation = HORIZONTAL_MIDDLE;
					}
					else {//All subsequent tiles
						if (tilesToRead[j - 1] == 'B' && tilesToRead[j + 1] == 'B')
							orientation = VERTICAL_TOP;
						else if (tilesToRead[j - 1] == 'B' && tilesToRead[j + 1] != 'B')
							orientation = HORIZONTAL_LEFT;
						else if (tilesToRead[j - 1] != 'B' && tilesToRead[j + 1] == 'B')
							orientation = HORIZONTAL_RIGHT;
						else
							orientation = HORIZONTAL_MIDDLE;
					}

					//Check the top and bottom adjacent tiles and set orientation
					if (previousTiles[j] != 'B' && futureTiles[j] != 'B') {
						if (orientation == HORIZONTAL_LEFT)
							orientation = LEFT;
						else if (orientation == HORIZONTAL_RIGHT)
							orientation = RIGHT;
						else
							orientation = INTERIOR;
					}
					else if (previousTiles[j] != 'B' && futureTiles[j] == 'B' && orientation == HORIZONTAL_MIDDLE) {
						orientation = BOTTOM;
					}
					else if (previousTiles[j] == 'B' && futureTiles[j] != 'B') {
						if (orientation == HORIZONTAL_LEFT)
							orientation = TOP_LEFT;
						else if (orientation == HORIZONTAL_RIGHT)
							orientation = TOP_RIGHT;
						else
							orientation = TOP_MIDDLE;
					}
					else if (previousTiles[j] == 'B' && futureTiles[j] == 'B' && orientation == VERTICAL_TOP){
						orientation = VERTICAL_MIDDLE;
					}
				}

				//Moving tile
				else if (tilesToRead[j] == 'R') { 
					type = MOVE;
				}

				//Swinging tile
				else if (tilesToRead[j] == 'G') {
					type = SWING;
				}

				//Add the tile
				if (type != BACKGROUND)
					AddTile(type, orientation, pivotPos, j, i);
			}
			
			//get a list of the previous tiles for tile initialization
			previousTiles = tilesToRead;
			tilesToRead = futureTiles;
		}

		fileRead.close();
		delete[] lvl_Data;
	}
}

//Check to see if the player is colliding with a transition tile
void LevelManager::TransitionCollisions(){
	for (unsigned i = 0; i < transitions.size(); i++){
		if (((player->position.y > transitions[i]->position.y && player->position.y < transitions[i]->position.y + transitions[i]->position.h)
			|| (player->position.h > transitions[i]->position.y && player->position.h < transitions[i]->position.y + transitions[i]->position.h))
			&& ((player->position.x + player->position.w - transitions[i]->position.x >= TRANSITION_DEPTH && player->position.x + player->position.w - transitions[i]->position.x < TILE_SIZE)
			|| (player->position.x - transitions[i]->position.x + transitions[i]->position.w <= -TRANSITION_DEPTH && player->position.x - transitions[i]->position.x + transitions[i]->position.w > -TILE_SIZE)))
			transitioning = true;
	}
}

//Add a tile based on the given parameters
void LevelManager::AddTile(TILE_TYPE type, TILE_ORIENTATION orientation, SDL_Point pivotPos, int locX, int locY) {
	Tile* tile = nullptr;
	
	switch (type) {
	case SWING:
		tile = new SwingingTile(SDL_Rect{ locX * TILE_SIZE, locY * TILE_SIZE, 0, 0 }, SDL_Rect{ 0,0,TILE_SIZE,TILE_SIZE }, 
			SDL_Point{ 0,0 }, type, orientation,
			lvlTransition->setting, SDL_Rect{ pivotPos.x, pivotPos.y, 0, 0 });
		break;
	case MOVE:
		tile = new MovingTile(SDL_Rect{ locX * TILE_SIZE, locY * TILE_SIZE, 0, 0 }, SDL_Rect{ 0,0,TILE_SIZE,TILE_SIZE },
			SDL_Point{ 0,0 }, type, orientation,
			lvlTransition->setting, SDL_Rect{ pivotPos.x, pivotPos.y, 0, 0 });
		break;
	case TRANSITION:
		transitions.push_back(new Tile(SDL_Rect{ locX * TILE_SIZE, locY * TILE_SIZE, 0, 0 }, SDL_Rect{ 0,0,TILE_SIZE,TILE_SIZE }, 
			SDL_Point{0,0}, type, orientation,
			lvlTransition->setting));
		break;
	default:
		tile = new Tile(SDL_Rect{ locX * TILE_SIZE, locY * TILE_SIZE, TILE_SIZE, TILE_SIZE }, SDL_Rect{ 0, 0,TILE_SIZE/2,TILE_SIZE/2 }, 
			SDL_Point{ 0,0 }, type, orientation,
			lvlTransition->setting);
		break;
	}

	if (tile != nullptr) {
		tile->loadTexture(textureFiles["TileSheet"], gRenderer);
		platforms->Add(tile);
	}
}

//Read in data loaded from file and append it to a string to read from
void LevelManager::ReadLevelData(char * lvlData, std::string& tileData, int startIndex, int lvlWidth) {
	tileData = "";
	for (int i = startIndex * lvlWidth; i < (startIndex + 1) * lvlWidth; i++) {
		tileData += lvlData[i];
	}
}