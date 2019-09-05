#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include "Player.h"

//constants for the window size
const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

//Three functions used for the main parts of the game loop
bool init();
bool loadMedia();
void close();

//window being rendered to
SDL_Window* window = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

SDL_Rect source = { 0, 0, 75, 78 };
SDL_Rect position = { 200, 200, 0, 0 };
Player player = { position, source, 0, 0 };

//Initalization function, handles all required logic for startup
bool init(){
	//Initialization flag
	bool success = true;

	//Initalize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Create the program window
		window = SDL_CreateWindow("Cool Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL) {
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
	player.loadTexture("Assets/WizardSpriteSheet.png", gRenderer);

	return success;
}

//Function that handles quitting out of the game
void close() {
	//Destroy the window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(window);
	window = NULL;
	gRenderer = NULL;

	//Quit all SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

//Main function, basic stuff that goes to the screen
int main(int argc, char* args[]) {
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
				while (SDL_PollEvent(&e) != 0){
					//User requests to exit
					if (e.type == SDL_QUIT){ 
						quit = true; 
					}

					//Call all necessary update methods
					player.UpdateState(e);
				}
				//Update all necessary position values
				player.Update();
				player.UpdatePosition();

				//Clear the screen
				SDL_RenderClear(gRenderer);
				
				//Call any draw methods for any gameobjects
				player.Draw(gRenderer);

				//Upate the screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}

	//Close SDL and all subsystems
	close();

	return 0;
}