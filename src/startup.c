#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../include/init.h"

int startupWindow() {
	SDL_Window* screen = SDL_CreateWindow("2048", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 600, SDL_WINDOW_OPENGL);
	int run = 1;
	Uint32 lastTick;
	Uint32 currentTick;
	int fps = 24;
	int sleep;
	double period = 1.0 / (double)fps * 1000;
	int milliPeriod = (int)period;
	int dimension;

	SDL_Event event;

	TTF_Font* font_regular;
	TTF_Font* font_small;
	TTF_Font* font_copyright;
	font_regular = loadFont("./ttf/OpenSans-Regular.ttf", 30);
	font_small = loadFont("./ttf/OpenSans-Regular.ttf", 20);
	font_copyright = loadFont("./ttf/OpenSans-Regular.ttf", 15);

	SDL_Rect text_rect = { 0, 0, 0, 0 };
	SDL_Surface* text_surface;
	SDL_Surface* window_surface = SDL_GetWindowSurface(screen);
	SDL_Color textColor = { 255, 255, 255 };

	text_surface = TTF_RenderText_Blended(font_regular, "Press a Number to choose Dimension!", textColor);
	text_rect.x = window_surface->w / 2 - text_surface->w / 2;
	text_rect.y = window_surface->h / 2 - text_surface->h / 2;
	SDL_BlitSurface(text_surface, NULL, window_surface, &text_rect);
	
	text_surface = TTF_RenderText_Blended(font_small, "4-8 for dimension AxA", textColor);
	text_rect.x = window_surface->w / 2 - text_surface->w / 2;
	text_rect.y = window_surface->h / 2 - text_surface->h / 2 +30;
	SDL_BlitSurface(text_surface, NULL, window_surface, &text_rect);
	
	text_surface = TTF_RenderText_Blended(font_small, "t for 5 min timebased game", textColor);
	text_rect.x = window_surface->w / 2 - text_surface->w / 2;
	text_rect.y = window_surface->h / 2 - text_surface->h / 2 +60;
	SDL_BlitSurface(text_surface, NULL, window_surface, &text_rect);
	
	text_surface = TTF_RenderText_Blended(font_copyright, "Copyright © 2017 Maximilian Schmidt and Bjoern Bargstaedt. All rights reserved.", textColor);
	text_rect.x = window_surface->w / 2 - text_surface->w / 2;
	text_rect.y = window_surface->h  - text_surface->h -10;
	SDL_BlitSurface(text_surface, NULL, window_surface, &text_rect);
	
	SDL_Surface* header;
	header=IMG_Load("img/header.png");
	text_rect.x=0;
	text_rect.y=0;
	SDL_BlitSurface(header, NULL, window_surface, &text_rect);

	SDL_UpdateWindowSurface(screen);

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
				case SDLK_t:
					dimension = 9;
					run = 0;
					break;
				case SDLK_ESCAPE:
					printf("EXIT!\n");
					exit(EXIT_SUCCESS);
				}
				break;
			case SDL_QUIT:
				printf("EXIT!\n");
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

