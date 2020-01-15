#include "LevelManager.h"

LevelManager::LevelManager(std::map<std::string, std::string> textures, SDL_Renderer* renderer){
	platforms = new ObjectTree(0, 0);
	movingPlatforms = new ObjectTree(0, 0);
	swingingPlatforms = new ObjectTree(0, 0);
	lvlTransition = new Transitioner();

	textureFiles = textures;
	gRenderer = renderer;

	player = new Player(SDL_Rect{ 0,0,75,78 }, SDL_Rect{ 0, 0, 75, 78 }, 12, 3);
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
		lvlTransition->roomNumber++;
		SDL_Point p = lvlTransition->Update();
		player->position.x = p.x;
		player->position.y = p.y;
		Init();
	}
}

//Render all relevant objects
void LevelManager::RenderAll(SDL_Renderer* renderer){
	if (platforms->count != 0) {
		platforms->Render(renderer);
	}
	if (movingPlatforms->count != 0) {
		movingPlatforms->Render(renderer);
	}
	if (swingingPlatforms->count != 0) {
		swingingPlatforms->Render(renderer);
	}
	player->Draw(renderer);
}

//Initialize the level, and reset from the last level
void LevelManager::Init(){
	std::ifstream fileRead(lvlTransition->roomName, std::ios::in | std::ios::binary | std::ios::beg);

	if (fileRead.is_open()){
		//Reset all data structs and read in the level dimensions
		fileRead.read(reinterpret_cast<char*>(&levelHeight), sizeof(levelHeight));
		fileRead.read(reinterpret_cast<char*>(&levelWidth), sizeof(levelWidth));
		platforms->Reset(levelWidth * TILE_SIZE, levelHeight * TILE_SIZE);
		movingPlatforms->Reset(levelWidth * TILE_SIZE, levelHeight * TILE_SIZE);
		swingingPlatforms->Reset(levelWidth * TILE_SIZE, levelHeight * TILE_SIZE);

		//Arrays to hold the tiles needing to be read
		char * futureTiles = new char[levelWidth];
		fileRead.read(futureTiles, levelWidth);
		std::string tilesToRead = futureTiles;
		std::string previousTiles = tilesToRead;

		//Enums denoting variables about the tile to be placed
		TileType type = Background;
		TileOrientation orientation = HorizontalMiddle;
		SDL_Point pivotPos = SDL_Point{0,0};

		//Loop through the entire level and add the tiles
		for (unsigned i = 0; i < levelHeight; i++){
			if (i < levelHeight - 1)
				fileRead.read(futureTiles, levelWidth);

			for (unsigned j = 0; j < levelWidth; j++){
				//Background spaces
				if (tilesToRead[j] == 'B') { 
					type = Background;
				}
				
				//Regular platforms
				else if (tilesToRead[j] == 'F') { 
					type = Platform;

					//Check the left and right adjacent tiles 
					if (j == 0) {//Check if its the first tile in the row
						if (tilesToRead[j + 1] == 'B')
							orientation = HorizontalRight;
						else
							orientation = HorizontalMiddle;
					}
					else if (j == levelWidth - 1) {//Check if its the last tile in the row
						if (tilesToRead[j - 1] == 'B')
							orientation = HorizontalLeft;
						else
							orientation = HorizontalMiddle;
					}
					else {//All subsequent tiles
						if (tilesToRead[j - 1] == 'B' && tilesToRead[j + 1] == 'B')
							orientation = VerticalTop;
						else if (tilesToRead[j - 1] == 'B' && tilesToRead[j + 1] != 'B')
							orientation = HorizontalLeft;
						else if (tilesToRead[j - 1] != 'B' && tilesToRead[j + 1] == 'B')
							orientation = HorizontalRight;
						else
							orientation = HorizontalMiddle;
					}

					//Check the top and bottom adjacent tiles and set orientation
					if (previousTiles[j] != 'B' && futureTiles[j] != 'B') {
						if (orientation == HorizontalLeft)
							orientation = Left;
						else if (orientation == HorizontalRight)
							orientation = Right;
						else
							orientation = Below;
					}
					else if (previousTiles[j] != 'B' && futureTiles[j] == 'B' && orientation == HorizontalMiddle) {
						orientation = Bottom;
					}
					else if (previousTiles[j] == 'B' && futureTiles[j] != 'B') {
						if (orientation == HorizontalLeft)
							orientation = TopLeft;
						else if (orientation == HorizontalRight)
							orientation = TopRight;
						else
							orientation = TopMiddle;
					}
					else if (previousTiles[j] == 'B' && futureTiles[j] == 'B' && orientation == VerticalTop){
						orientation = VerticalMiddle;
					}
				}

				//Moving tile
				else if (tilesToRead[j] == 'R') { 
					type = Move;
				}

				//Swinging tile
				else if (tilesToRead[j] == 'G') {
					type = Swing;
				}

				//Add the tile
				if (type != Background)
					AddTile(type, orientation, pivotPos, j, i);
			}
			
			//get a list of the previous tiles for tile initialization
			previousTiles = tilesToRead;
			tilesToRead = futureTiles;
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
		tile = new SwingingTile(SDL_Rect{ locX * TILE_SIZE, locY * TILE_SIZE, 0, 0 }, SDL_Rect{ 0,0,TILE_SIZE,TILE_SIZE }, 0, 0, type, orientation,
			lvlTransition->setting, SDL_Rect{ pivotPos.x, pivotPos.y, 0, 0 });
		tile->loadTexture(textureFiles["TileSheet"], gRenderer);
		swingingPlatforms->Add(tile);
		break;
	case Move:
		tile = new MovingTile(SDL_Rect{ locX * TILE_SIZE, locY * TILE_SIZE, 0, 0 }, SDL_Rect{ 0,0,TILE_SIZE,TILE_SIZE }, 0, 0, type, orientation,
			lvlTransition->setting, SDL_Rect{ pivotPos.x, pivotPos.y, 0, 0 });
		tile->loadTexture(textureFiles["TileSheet"], gRenderer);
		movingPlatforms->Add(tile);
		break;
	case Transition:
		transitions.push_back(new Tile(SDL_Rect{ locX * TILE_SIZE, locY * TILE_SIZE, 0, 0 }, SDL_Rect{ 0,0,TILE_SIZE,TILE_SIZE }, 0, 0, type, orientation,
			lvlTransition->setting));
		break;
	default:
		tile = new Tile(SDL_Rect{ locX * TILE_SIZE, locY * TILE_SIZE, TILE_SIZE, TILE_SIZE }, SDL_Rect{ 0, 0,TILE_SIZE/2,TILE_SIZE/2 }, 0, 0, type, orientation,
			lvlTransition->setting);
		tile->loadTexture(textureFiles["TileSheet"], gRenderer);
		platforms->Add(tile);
		break;
	}
}

void LevelManager::SetViewport(){

}