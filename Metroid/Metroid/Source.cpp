//#include <SDL.h>
//#include <SDL_image.h>
#include "World.h"

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

//constants for the window size
const int WINDOW_WIDTH = 1920;
const int WINDOW_HEIGHT = 1080;

//Three functions used for the main parts of the game loop
bool init();
bool loadMedia();
void close();
void wrapper();

//window being rendered to
SDL_Window* window = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

World* world;
SDL_Rect display;

//function to get the display bounds and set the resolution
bool SetDisplay (){
	bool success = true;
	if (SDL_GetDisplayBounds(0, &display) != 0) {
		success = false;
	}
	//float size = (float)display.w / (float)display.h;
	//float otherSize = 1920.f / 1080.f;
	window = SDL_CreateWindow("Cool Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, display.w, display.h, SDL_WINDOW_SHOWN);
	if (window == NULL) 
		success = false;
	return success;
}

//Initalization function, handles all required logic for startup
bool init(){
	//Initialization flag
	bool success = true;

	//Initalize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		success = false;
	}
	else
	{
		//Create the program window
		if (!SetDisplay()) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Create the renderer for the window
			gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL){
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else{
				//Initialize the renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				//Set the resolution scaling base
				SDL_RenderSetLogicalSize(gRenderer, 1920, 1080);
				//Initalize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SD:_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

//Function that handles loading in assets
bool loadMedia() {
	//Loading flag
	bool success = true;

	//Load in all assets
	world = new World(gRenderer);
	world->LoadLevel();

	return success;
}

//Function that handles quitting out of the game
void close() {
	//Destroy the window
	delete world;
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(window);
	window = NULL;
	gRenderer = NULL;

	//Quit all SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

//wrapper function for memory leak detection
void wrapper() {
	//Startup SDL and create a new window
	if (!init()) {
		printf("Failed to initialize!\n");
	}
	else {
		//Load all media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			//Main loop flag
			bool quit = false;
			SDL_Event e;
			
			//Hold the application running
			while (!quit) {
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0) {
					//User requests to exit
					if (e.type == SDL_QUIT) {
						quit = true;
					}
				}
				//Update all necessary position values
				world->Update();

				//Clear the screen
				SDL_RenderClear(gRenderer);

				//Call any draw methods for any gameobjects
				world->Render();
				
				//Upate the screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Close SDL and all subsystems
	close();
}

//Main function, basic stuff that goes to the screen
int main(int argc, char *args[]) {
	wrapper();
	_CrtDumpMemoryLeaks();
	
	return 0;
}