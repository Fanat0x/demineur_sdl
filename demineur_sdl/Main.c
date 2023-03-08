#include "stdio.h"
#include "SDL.h"
#undef main

typedef int bool;
#define true 1;
#define false 0;

//don't do this, this is just an example
void update();
void render(SDL_Renderer* renderer, SDL_Window* window, int tableau[10][10]);
void displayGrid(SDL_Renderer* renderer, SDL_Window* window, int tableau[10][10]);


//please don't put all your code in main like I did.
int main() {

	int tableau[10][10];
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Rect rectangleTest;
	bool isRunning = true;
	bool fullscreen;

	fullscreen = false;
	int flags = 0;
	flags = SDL_WINDOW_RESIZABLE;
	if (fullscreen) {
		flags = flags | SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) 
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

	

	while (isRunning) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			default:
				break;
			}
		}
		update();
		render(renderer, window, tableau);
	}

	//frees memory associated with renderer and window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);	//error here
	SDL_Quit();


	return 0;
}


//simple render function
void render(SDL_Renderer* renderer, SDL_Window* window, int tableau[10][10]) {
	SDL_SetRenderDrawColor(renderer, 121, 121, 121, 255);
	

	//your stuff to render would typically go here.
	displayGrid(renderer, window, tableau);
	
}

//simple update function
void update() {
	//if things could update the code would go in here.
}

void displayGrid(SDL_Renderer* renderer, SDL_Window* window, int tableau[10][10])
{
	SDL_RenderClear(renderer);
	SDL_Surface* imageCase = NULL;
	SDL_Texture* texture = NULL;
	SDL_Rect rectangleTest;

	imageCase = SDL_LoadBMP("img/grass.bmp");

	texture = SDL_CreateTextureFromSurface(renderer, imageCase);
	
	SDL_FreeSurface(imageCase);

	SDL_QueryTexture(texture, NULL, NULL, &rectangleTest.h, &rectangleTest.w);

	rectangleTest.x = 0;
	rectangleTest.y = 0;

	int i = 0;
	int j = 0;

	for (i = 0; i < 10; i++)
	{
		rectangleTest.y = 50 * i;
		for (j = 0; j < 10; j++)
		{
			rectangleTest.x = 50 * j;
			SDL_RenderCopy(renderer, texture, NULL, &rectangleTest);
		}
	}
	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture);
}