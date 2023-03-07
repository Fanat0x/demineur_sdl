#include "stdio.h"
#include "SDL.h"
#undef main

typedef int bool;
#define true 1;
#define false 0;

//don't do this, this is just an example
SDL_Renderer* renderer;
SDL_Window* window;
bool isRunning;
bool fullscreen;
void handleEvents();
void update();
void render();


//please don't put all your code in main like I did.
int main() {

	fullscreen = false;
	int flags = 0;
	flags = SDL_WINDOW_RESIZABLE;
	if (fullscreen) {
		flags = flags | SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		printf( "Subsystems Initialized!\n");

		window = SDL_CreateWindow("Demineur", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, flags);
		if (window) {
			printf("Window Created!\n");
			SDL_SetWindowMinimumSize(window, 100, 100);
		}
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 121, 121, 121, 255);
			printf("Renderer created!\n");
			SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
			isRunning = true;
		}

	}

	while (isRunning) {
		handleEvents();
		update();
		render();
	}

	//frees memory associated with renderer and window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);	//error here
	SDL_Quit();


	return 0;
}

//handles any events that SDL noticed.
void handleEvents() {
	//the only event we'll check is the  SDL_QUIT event.
	SDL_Event event;
	SDL_PollEvent(&event);


	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

//simple render function
void render() {
	SDL_SetRenderDrawColor(renderer, 121, 121, 121, 255);
	SDL_RenderClear(renderer);

	//your stuff to render would typically go here.
	SDL_Surface* imageCase = NULL;
	SDL_Texture* texture = NULL;
	SDL_Rect rectangleTest;

	imageCase = SDL_LoadBMP("img/pingouin.bmp");

	texture = SDL_CreateTextureFromSurface(renderer, imageCase);
	SDL_FreeSurface(imageCase);

	SDL_QueryTexture(texture, NULL, NULL, &rectangleTest.w, &rectangleTest.h);

	rectangleTest.x = 500 / 2 - rectangleTest.w / 2;
	rectangleTest.y = 500 / 2 - rectangleTest.h / 2;

	SDL_RenderCopy(renderer, texture, NULL, &rectangleTest);
	SDL_RenderPresent(renderer);
}

//simple update function
void update() {
	//if things could update the code would go in here.
}