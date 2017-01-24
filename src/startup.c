#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

int startupWindow() {
	SDL_Window* screen = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 200, 200, SDL_WINDOW_OPENGL);
	int run = 1;
	Uint32 lastTick;
	Uint32 currentTick;
	int fps = 24;
	int sleep;
	double period = 1.0 / (double)fps * 1000;
	int milliPeriod = (int)period;
	int dimension;

	SDL_Event event;

	while (run) {
		lastTick = SDL_GetTicks();

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
				case SDLK_4:
					dimension = 4;
					run = 0;
					break;
				case SDLK_5:
					dimension = 5;
					run = 0;
					break;
				case SDLK_6:
					dimension = 6;
					run = 0;
					break;
				case SDLK_7:
					dimension = 7;
					run = 0;
					break;
				case SDLK_8:
					dimension = 8;
					run = 0;
					break;
				}
				break;
			case SDL_QUIT:
				exit(EXIT_SUCCESS);
			}
		}

		currentTick = SDL_GetTicks();

		sleep = milliPeriod - (currentTick - lastTick);
		if (sleep < 0) sleep = 0;
		SDL_Delay(sleep);
	}

	SDL_DestroyWindow(screen);
	return dimension;
}

