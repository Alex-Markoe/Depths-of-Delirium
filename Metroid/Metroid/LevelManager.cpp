#include "LevelManager.h"

LevelManager::LevelManager(std::map<std::string, std::string> textures, SDL_Renderer* renderer){
	platforms = new ObjectTree(0, 0);
	movingPlatforms = new ObjectTree(0, 0);
	swingingPlatforms = new ObjectTree(0, 0);

	textureFiles = textures;
	gRenderer = renderer;

	player = new Player(SDL_Rect{ 0,0,0,0 }, SDL_Rect{ 0, 0, 75, 78 }, 0, 0);
	player->loadTexture(textureFiles["PlayerSheet"], renderer);

	transitioning = false;
}


LevelManager::~LevelManager(){
	
}

//Call all update methods of any objects in the level
void LevelManager::Update(){
	//Update all the objects in the level
	player->Update();

	//Check collisions
	if (platforms->count != 0){
		platforms->CollisionDetector(*player);
	}
	if (movingPlatforms->count != 0){
		MovingPlatformUpdate();
		movingPlatforms->UpdatePosition();

		movingPlatforms->CollisionDetector(*player);
	}
	if (swingingPlatforms->count != 0) {
		SwingingPlatformUpdate();
		swingingPlatforms->UpdatePosition();

		swingingPlatforms->CollisionDetector(*player);
	}

	//Change positions
	player->UpdatePosition();

	//Change the level if a transition is hit
	TransitionCollisions();
	if (transitioning){
		lvlTransition.roomNumber++;
		SDL_Point p = lvlTransition.Update();
		player->position.x = p.x;
		player->position.y = p.y;
		Init();
	}
}

//Call any update methods that require user input
void LevelManager::StateUpdate(SDL_Event e){
	player->UpdateState(e);
}

//Render all relevant objects
void LevelManager::RenderAll(SDL_Renderer* renderer){
	player->Draw(renderer);

	if (platforms->count != 0) {
		platforms->Render(renderer);
	}
	if (movingPlatforms->count != 0) {
		movingPlatforms->Render(renderer);
	}
	if (swingingPlatforms->count != 0) {
		swingingPlatforms->Render(renderer);
	}
}

//Initialize the level, and reset from the last level
void LevelManager::Init(){
	std::ifstream fileRead(lvlTransition.roomName, std::ios::in | std::ios::binary | std::ios::beg);

	if (fileRead.is_open()){
		fileRead.read(reinterpret_cast<char*>(&levelHeight), sizeof(levelHeight));
		fileRead.read(reinterpret_cast<char*>(&levelWidth), sizeof(levelWidth));

		char tile = '.';
		char prevTile = '.';
		char * nextTile;
		char * prevTiles = new char[levelWidth];

		TileType type = Platform;
		TileOrientation orientation = Middle;
		SDL_Point pivotPos;

		for (int i = 0; i < levelHeight; i++){
			char * currTiles = new char[levelWidth];

			//Loop through each element in the row
			for (int j = 0; j < levelWidth; j++){
				fileRead.read(nextTile, 1);
				currTiles[j] = *nextTile;

				//Determine what the tile should look like
				if(i == 0){ //First row of tiles
					if (j >= 1){
						if (tile == 'B'){
							if (prevTile == '.' && *nextTile == '.'){
								type = Platform;
								orientation = Middle;
							}
							else if (prevTile == '.' && *nextTile == '.') {
								type = Platform;
								orientation = Middle;
							}
							else{
								type = Platform;
								orientation = Middle;
							}
						}

						AddTile(type, orientation, pivotPos, j, i); //Add the tile
					}

					if (j == levelWidth - 1){ //Special logic if it's the last tile
						if (prevTile == '.'){
							type = Platform;
							orientation = Middle;
						}
						else{
							type = Platform;
							orientation = Middle;
						}

						AddTile(type, orientation, pivotPos, j, i); //Add the tile
					}
				}

				else{ //All subsequent rows
					if (j >= 1) {
						if (tile == 'B'){
							if (prevTile == '.' && *nextTile == '.') {
								if (prevTiles[j] == 'B'){
									type = Platform;
									orientation = Middle;
								}
								else{
									type = Platform;
									orientation = Middle;
								}
							}
							else if (prevTile == '.' && *nextTile == '.') {
								if (prevTiles[j] == 'B') {
									type = Platform;
									orientation = Middle;
								}
								else {
									type = Platform;
									orientation = Middle;
								}
							}
							else {
								if (prevTiles[j] == 'B') {
									type = Platform;
									orientation = Middle;
								}
								else {
									type = Platform;
									orientation = Middle;
								}
							}
						}

						AddTile(type, orientation, pivotPos, j, i); //Add the tile
					}

					

					if (j == levelWidth - 1) { //Special logic if it's the last tile
						if (prevTile == '.') {
							if (prevTiles[j] == 'B') {
								type = Platform;
								orientation = Middle;
							}
							else {
								type = Platform;
								orientation = Middle;
							}
						}
						else {
							if (prevTiles[j] == 'B') {
								type = Platform;
								orientation = Middle;
							}
							else {
								type = Platform;
								orientation = Middle;
							}
						}

						AddTile(type, orientation, pivotPos, j, i); //Add the tile
					}
				}

				//Add the new object
				

				//Update the tiles
				tile = *nextTile;
				prevTile = tile;
			}
			
			//get a list of the previous tiles for tile initialization
			delete[] prevTiles;
			prevTiles = new char[levelWidth];
			for (int k = 0; k < levelWidth; k++){
				prevTiles[k] = currTiles[k];
			}
			delete[] currTiles;

			char tile = '.';
			char prevTile = '.';
		}
	}
}

//Method that updates all moving platforms based on their position in the level
void LevelManager::MovingPlatformUpdate(){
	std::vector<GameObject*> items = movingPlatforms->AllObjects();

	for (unsigned i = 0; i < items.size(); i++){
		MovingTile* tile = (MovingTile*)items[i];

		if (tile->position.x > tile->destinationPosition.x || tile->position.y > tile->destinationPosition.y
			|| tile->position.x < tile->initialPosition.x || tile->position.y < tile->initialPosition.y)
			tile->velocity = {tile->velocity.x * -1, tile->velocity.y * -1};
	}
}

//Update all swinging platforms and their positions every frame
void LevelManager::SwingingPlatformUpdate(){
	std::vector<GameObject*> items = swingingPlatforms->AllObjects();

	for (unsigned i = 0; i < items.size(); i++){
		SwingingTile* tile = (SwingingTile*)items[i];

		/*float angle = 90.f - atan((tile->pivot.y - (tile->position.y + (tile->position.h / 2))) / (tile->pivot.x - (tile->position.x + (tile->position.w / 2))));
		float gravity = sin(angle) * GRAVITY;*/

		SDL_Point gravOrigin = {(tile->position.x + (tile->position.w / 2)) - tile->pivot.x, (tile->position.y + (tile->position.h / 2)) - tile->pivot.y};
		SDL_Point gravDest = {(tile->position.x + (tile->position.w / 2)), (tile->position.y + (tile->position.h / 2)) + GRAVITY};
		tile->velocity.x += gravDest.x - gravOrigin.x;
		tile->velocity.y += gravDest.y - gravOrigin.y;
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
void LevelManager::AddTile(TileType type, TileOrientation orientation, SDL_Point pivotPos, int locX, int locY) {
	Tile* tile;
	
	switch (type) {
	case Swing:
		tile = new SwingingTile(SDL_Rect{ locX * TILE_SIZE, locY * TILE_SIZE, 0, 0 }, SDL_Rect{ 0,0,0,0 }, 0, 0, type, orientation,
			lvlTransition.setting, SDL_Rect{ pivotPos.x, pivotPos.y, 0, 0 });
		tile->loadTexture(textureFiles["TileSheet"], gRenderer);
		swingingPlatforms->Add(tile);
		break;
	case Move:
		tile = new MovingTile(SDL_Rect{ locX * TILE_SIZE, locY * TILE_SIZE, 0, 0 }, SDL_Rect{ 0,0,0,0 }, 0, 0, type, orientation,
			lvlTransition.setting, SDL_Rect{ pivotPos.x, pivotPos.y, 0, 0 });
		tile->loadTexture(textureFiles["TileSheet"], gRenderer);
		movingPlatforms->Add(tile);
		break;
	case Transition:
		transitions.push_back(new Tile(SDL_Rect{ locX * TILE_SIZE, locY * TILE_SIZE, 0, 0 }, SDL_Rect{ 0,0,0,0 }, 0, 0, type, orientation,
			lvlTransition.setting));
		break;
	default:
		tile = new Tile(SDL_Rect{ locX * TILE_SIZE, locY * TILE_SIZE, 0, 0 }, SDL_Rect{ 0,0,0,0 }, 0, 0, type, orientation,
			lvlTransition.setting);
		tile->loadTexture(textureFiles["TileSheet"], gRenderer);
		platforms->Add(tile);
		break;
	}
}

void LevelManager::SetViewport(){

}