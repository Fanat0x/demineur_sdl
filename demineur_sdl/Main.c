#include "stdio.h"
#include "SDL.h"
#undef main
#include "stdbool.h"

void update();
void render(SDL_Renderer* renderer, SDL_Window* window, int tableau[10][10]);
void displayGrid(SDL_Renderer* renderer, SDL_Window* window, int tableau[10][10]);

void render(SDL_Renderer* renderer, SDL_Window* window, int tableau[10][10])
{
	SDL_SetRenderDrawColor(renderer, 121, 121, 121, 255);
	displayGrid(renderer, window, tableau);
}

void update()
{

}

void displayGrid(SDL_Renderer* renderer, SDL_Window* window, int tableau[10][10])
{
	SDL_RenderClear(renderer);
	SDL_Surface* imageCase = NULL;
	SDL_Texture* texture = NULL;
	SDL_Rect rectangle;

	rectangle.x = 0;
	rectangle.y = 0;

	int i = 0;
	int j = 0;

	for (i = 0; i < 10; i++)
	{
		rectangle.y = 50 * i;
		for (j = 0; j < 10; j++)
		{
			if ((i + j) % 2 == 0)
			{
				imageCase = SDL_LoadBMP("img/grass.bmp");
			}
			else
			{
				imageCase = SDL_LoadBMP("img/grass2.bmp");
			}
			rectangle.x = 50 * j;
			texture = SDL_CreateTextureFromSurface(renderer, imageCase);
			SDL_FreeSurface(imageCase);
			SDL_QueryTexture(texture, NULL, NULL, &rectangle.h, &rectangle.w);
			
			SDL_RenderCopy(renderer, texture, NULL, &rectangle);
			SDL_DestroyTexture(texture);
		}
		
	}

	SDL_RenderPresent(renderer);
	SDL_DestroyTexture(texture);
}

int main()
{

	int tableau[10][10];
	SDL_Renderer* renderer;
	SDL_Window* window;
	SDL_Rect rectangle;
	bool isRunning = true;
	bool fullscreen;

	float deltaTime = 0;
	int time = 0;
	int FPSTarget = 60;
	float deltaTimeTarget = 1000 / (float)FPSTarget;

	fullscreen = false;
	int flags = 0;
	flags = SDL_WINDOW_RESIZABLE;
	if (fullscreen) {
		flags = flags | SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
		printf("Subsystems Initialized!\n");

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
		deltaTime = SDL_GetTicks() - time;

		if (deltaTime < deltaTimeTarget) {
			SDL_Delay(deltaTimeTarget - deltaTime);
			deltaTime = deltaTimeTarget;
		}
		else
			system("cls");
			printf("%f\n", deltaTime);
		update();
		render(renderer, window, tableau);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}